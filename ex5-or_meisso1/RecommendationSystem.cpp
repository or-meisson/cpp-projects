
#include "RecommendationSystem.h"
#include <memory>
#include <vector>
#include <cmath>
#include <algorithm>
#include <limits>

std::ostream &operator<< (std::ostream &os, RecommendationSystem &recSystem)
{
  for (const auto &movie: recSystem.movies_set_1)
  {
	os << *movie;
  }
  return os;
}

/**
 * Calculates the Euclidean norm (magnitude) of a given vector.
 *
 * @param vec The input vector for which the norm is calculated.
 * @return The Euclidean norm of the input vector.
 */
double RecommendationSystem::calc_norm (const std::vector<double> &vec)
{
  double sum_of_squares = 0.0;
  for (const double &element: vec)
  {
	sum_of_squares += element * element;
  }
  
  return std::sqrt (sum_of_squares);
}

/**
 * Calculates the scalar product (dot product) of two given vectors.
 *
 * @param vec1 The first input vector.
 * @param vec2 The second input vector.
 * @return The scalar product (dot product) of the two input vectors.
 */
double RecommendationSystem::calc_scalar_product\
(const std::vector<double> &vec1, const
std::vector<double> &vec2)
{
  double dot_product = 0.0;
  for (std::size_t i = 0; i < vec1.size (); i++)
  {
	dot_product += vec1[i] * vec2[i];
  }
  return dot_product;
}


RecommendationSystem::RecommendationSystem () = default;

sp_movie RecommendationSystem::add_movie (const std::string &name, int year,
										  const
										  std::vector<double> &features)
{
  sp_movie smart_ptr_movie = std::make_shared<Movie> (name, year);
  movie_key movie_key_1 = std::make_pair (name, year);
  movie_value movie_value_1 = std::make_pair (smart_ptr_movie, features);
  rec_system_ptr[movie_key_1] = movie_value_1;
  movies_set_1.insert (smart_ptr_movie);
  
  return smart_ptr_movie;
  
}

sp_movie RecommendationSystem::get_movie (const std::string &name, int year)
{
  movie_key key = std::make_pair (name, year);
  
  if (rec_system_ptr.count (key) == 0)
  {
	return nullptr;
  }
  return rec_system_ptr[key].first;
}



sp_movie RecommendationSystem::recommend_by_content (const User &user){
  rank_map user_rank_map = user.get_ranks ();
  double sum = 0;
  double quantity = 0;
  for (const auto &elem: user_rank_map){
	sum += elem.second;
	quantity++;
  }
  double mean = sum / quantity;
  size_t size = 0;
  std::vector<double> pref_vector (size, 1);
  for (const auto &elem: user_rank_map){
	if (user_rank_map.count (elem.first) > 0){
	  double normalized = elem.second - mean;
	  movie_key movie_key_1 = std::make_pair (elem.first->get_name (), elem
		  .first->get_year ());
	  size = rec_system_ptr[movie_key_1].second.size ();
	  pref_vector.resize (size);
	  std::vector<double> pref_vec_for_cur_movie = \
          rec_system_ptr[movie_key_1].second;
	  for (std::size_t i = 0; i < pref_vec_for_cur_movie.size (); i++){
		pref_vector[i] =
			pref_vector[i] + pref_vec_for_cur_movie[i] * normalized;
	  }
	}
  }
  double max_rank = -std::numeric_limits<double>::infinity ();
  movie_key best_movie;
  for (const auto &movie_elem: rec_system_ptr){
	sp_movie movie_ptr = movie_elem.second.first;
	if (user_rank_map.count (movie_ptr) == 0){
	  movie_key movie_key_1 = std::make_pair (movie_ptr->get_name (),\
											  movie_ptr->get_year ());
	  std::vector<double> pref_vec_for_cur_movie = \
          rec_system_ptr[movie_key_1].second;
	  double pref_vec_norm = calc_norm (pref_vector);
	  double pref_vec_for_cur_movie_norm = calc_norm \
		  (pref_vec_for_cur_movie);
	  double scalar_prod = calc_scalar_product (pref_vector,
												pref_vec_for_cur_movie);
	  double cur_rank = scalar_prod / (pref_vec_norm *
									   pref_vec_for_cur_movie_norm);
	  if (cur_rank > max_rank){
		max_rank = cur_rank;
		best_movie = movie_key_1;
	  }
	}
  }
  return rec_system_ptr[best_movie].first;
}

/**
 * Compare function for sorting pairs based on the second element in
 * descending order.
 *
 * @param p1 The first pair to compare.
 * @param p2 The second pair to compare.
 * @return `true` if the second element of `p1` is greater than the second
 * element of `p2`, `false` otherwise.
 */
bool RecommendationSystem::compare_second (const
std::pair<std::shared_ptr<Movie>, double> &p1,
					 const std::pair<std::shared_ptr<Movie>, double> &p2)
{
  return p1.second > p2.second;
}

double RecommendationSystem::predict_movie_score (const User &user, const
sp_movie &movie, int k)
{
  rank_map user_rank_map = user.get_ranks ();
  std::vector<std::pair<sp_movie, double>> similarity_of_movies;
  
  movie_key movie_key_1 = std::make_pair (movie->get_name (),
										  movie->get_year ());
  std::vector<double> chosen_m_movie = rec_system_ptr[movie_key_1].second;
  for (const auto &elem: user_rank_map)
  {
	if (user_rank_map.count (elem.first) > 0)
	{
	  movie_key movie_key_2 = std::make_pair (elem.first->get_name (), elem
		  .first->get_year ());
	  std::vector<double> pref_vec_for_cur_movie =
		  rec_system_ptr[movie_key_2].second;
	  double m_movie_vec_norm = calc_norm (chosen_m_movie);
	  double pref_vec_for_cur_movie_norm = calc_norm (pref_vec_for_cur_movie);
	  double scalar_prod = calc_scalar_product (chosen_m_movie,
												pref_vec_for_cur_movie);
	  double similarity = (scalar_prod / (m_movie_vec_norm *
										  pref_vec_for_cur_movie_norm));
	  similarity_of_movies.emplace_back (elem.first, similarity);
	}
  }
  std::sort (similarity_of_movies.begin (), similarity_of_movies.end (),\
			 compare_second);
  similarity_of_movies.resize (k);
  double upper_sum = 0;
  double down_sum = 0;
  for (const auto &pair: similarity_of_movies)
  {
	upper_sum += pair.second * user_rank_map[pair.first];
	down_sum += pair.second;
  }
  return upper_sum / down_sum;
}

sp_movie RecommendationSystem::recommend_by_cf (const User &user, int k)
{
  rank_map user_rank_map = user.get_ranks ();
  double max_rank = -std::numeric_limits<double>::infinity ();
  sp_movie best_movie;
  
  for (const auto &elem: rec_system_ptr)
  {
	if (user_rank_map.count (elem.second.first) == 0)
	{
	  double score = predict_movie_score (user, elem.second.first, k);
	  if (score > max_rank)
	  {
		best_movie = elem.second.first;
		max_rank = score;
	  }
	}
  }
  return best_movie;
}





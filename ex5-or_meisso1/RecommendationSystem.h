
#ifndef RECOMMENDATIONSYSTEM_H
#define RECOMMENDATIONSYSTEM_H
#include "User.h"
#include "vector"
#include <map>

typedef struct compare_movies
{
	bool operator() (const sp_movie &movie1, const sp_movie &movie2) const
	{
	  return *movie1 < *movie2;
	}
} compare_movies;

typedef std::pair<sp_movie, std::vector<double>> movie_value;

typedef std::pair<std::string, int> movie_key;

typedef std::map<movie_key, movie_value> recomendation_system;

typedef std::set<sp_movie, compare_movies> movies_set;

class RecommendationSystem
{
 private:
  recomendation_system rec_system_ptr; //todo האמנם?
  movies_set movies_set_1;
  
  static double calc_norm (const std::vector<double> &vec);
  static double calc_scalar_product (const std::vector<double> &vec1, const
  std::vector<double> &vec2);
  static bool compare_second (const std::pair<std::shared_ptr<Movie>
      , double> &p1,const std::pair<std::shared_ptr<Movie>, double> &p2);
 
 
 
 public:
  
  //explicit RecommendationSystem()
  RecommendationSystem ();
  /**
   * adds a new movie to the system
   * @param name name of movie
   * @param year year it was made
   * @param features features for movie
   * @return shared pointer for movie in system
   */
  sp_movie add_movie (const std::string &name, int year, \
                       const std::vector<double> &features);
  
  /**
   * a function that calculates the movie with highest score based
   * on movie features
   * @param ranks user ranking to use for algorithm
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_content (const User &user);
  
  /**
   * a function that calculates the movie with highest predicted score
   * based on ranking of other movies
   * @param ranks user ranking to use for algorithm
   * @param k
   * @return shared pointer to movie in system
   */
  sp_movie recommend_by_cf (const User &user, int k);
  
  /**
   * Predict a user rating for a movie given argument using item cf
   * procedure with k most similar movies.
   * @param user_rankings: ranking to use
   * @param movie: movie to predict
   * @param k:
   * @return score based on algorithm as described in pdf
   */
  double predict_movie_score (const User &user, const sp_movie &movie,
							  int k);
  
  /**
   * gets a shared pointer to movie in system
   * @param name name of movie
   * @param year year movie was made
   * @return shared pointer to movie in system
   */
  sp_movie get_movie (const std::string &name, int year);
  
  /**
   * Overloaded output stream operator for the RecommendationSystem class.
   * @param os The output stream.
   * @param recommendation_system The RecommendationSystem object to
   * be printed.
   * @return The output stream.
   */
  friend std::ostream &operator<< (std::ostream &os, RecommendationSystem &
  recommendation_system);
  
};

#endif //RECOMMENDATIONSYSTEM_H



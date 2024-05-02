
#include "User.h"

#include "RecommendationSystem.h"


// implement your cpp code here


User::User (const std::string& name, const rank_map &rank_map_,
			_rs& rec_system_ptr)
{
  this->user_name = name;
  this->rank_map_ = rank_map_;
  this->rec_system_ptr = rec_system_ptr;
}

std::string User::get_name () const
{ return user_name; }

void User::add_movie_to_rs (const std::string &name, int year,
					  const std::vector<double> &features,
					  double rate)
{
  sp_movie movie = (*rec_system_ptr).add_movie(name, year, features);
  rank_map_[movie] = rate;
  
}


rank_map User::get_ranks() const{
  return rank_map_;
}

sp_movie User::get_recommendation_by_content() const{
  return (*rec_system_ptr).recommend_by_content(*this);
}


double User::get_prediction_score_for_movie(const std::string& name, int year,
										  int k) const{
//  std::pair<std::string, int> movie_key = std::make_pair (name, year);
  sp_movie movie = (*rec_system_ptr).get_movie (name, year);
  return (*rec_system_ptr).predict_movie_score(*this, movie, k);

}


sp_movie User::get_recommendation_by_cf(int k) const{
  return (*rec_system_ptr).recommend_by_cf(*this, k);
}


std::ostream& operator<<(std::ostream& os, const User& user){
  os << "Name: " << user.get_name() << "\n" << *(user.rec_system_ptr)
  <<std::endl;
  return os;
}

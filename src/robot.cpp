#include "robot.h"

// Default c-tor
Robot::Robot() : x_pos_(0), y_pos_(0), orientation_(South) {}

// Parameterized c-tor
Robot::Robot(const int x_pos, const int y_pos, const CardinalDirection orientation, const PhysicalMap map) : x_pos_(x_pos), y_pos_(y_pos), orientation_(orientation), map_(map) {}


// updates robot's map based on sensor readings
void Robot::rayCasting() {
  if(orientation_ == North) {
    rayRange(0, 180);
  } else if (orientation_ == East) {
    rayRange(-90, 90);
  } else if (orientation_ == South) {
    rayRange(180, 360);
  } else if (orientation_ == West) {
    rayRange(90, 270);
  }
}

// casts rays from start to end
// start and end should be 180 degrees apart
void Robot::rayRange(const int start, const int end) {
  for (int i = start; i <= end; i += 15) {
    const int actual_direction = localize(i);
    
    ray(actual_direction);
  }
}

// casts ray and updates probabilities
// direction should be from 0 to 359 degrees
void Robot::ray(const int direction) {
  int temp_quartile = -1;
  
  if (direction >= 0 && direction < 90) {
    temp_quartile = 0;
  }
  else if (direction >= 90 && direction < 180) {
    temp_quartile = 1;
  }
  else if (direction >= 180 && direction < 270) {
    temp_quartile = 2;
  }
  else if (direction >= 270 && direction < 360) {
    temp_quartile = 3;
  }
  
  const int quartile = temp_quartile;
  
  int temp_x_step = Positive;
  int temp_y_step = Negative;
  
  if (quartile == 0) {
    temp_x_step = Positive;
    temp_y_step = Negative;
  }
  else if (quartile == 1) {
    temp_x_step = Negative;
    temp_y_step = Negative;
  }
  else if (quartile == 2) {
    temp_x_step = Negative;
    temp_y_step = Positive;
  }
  else if (quartile == 3) {
    temp_x_step = Positive;
    temp_y_step = Positive;
  }
  
  const int x_step = temp_x_step;
  const int y_step = temp_y_step;
  
  const float direction_rads = toRadians(direction);
  const float slope = tan(direction_rads);
  
  float ray_distance = 0.0f;
  float ray_x = (float) x_pos_;
  float ray_y = (float) y_pos_;
  int x_read = x_pos_;
  int y_read = y_pos_;
  
  
  while (ray_distance < 50.0f) {
    ray_x += x_step * 1.0f;
    ray_y = slope * ray_x;
    
    bool horizontal = false;
    const int proposed_y = y_read + y_step;
    if (y_step == Positive) {
      if (ray_y > proposed_y) {
        horizontal = false;
      }
      else if (ray_y < proposed_y) {
        horizontal = true;
      }
    }
    else if (y_step == Negative) {
      if (ray_y < proposed_y) {
        horizontal = false;
      }
      else if (ray_y > proposed_y) {
        horizontal = true;
      }
    }
    
    int temp_target_x = -1;
    int temp_target_y = -1;
    
    if (horizontal) {
      temp_target_x = x_read + x_step;
      temp_target_y = y_read;
    }
    else {
      temp_target_x = x_read;
      temp_target_y = y_read + y_step;
    }
    
    const int target_x = temp_target_x;
    const int target_y = temp_target_y;
    
    int temp_target_index = -1;
    
    if (map_.inBounds(target_x, target_y)) {
      temp_target_index = map_.index(target_x, target_y);
    }
    else {
      break;
    }
    
    const int this_index = map_.index(x_read, y_read);
    const int target_index = temp_target_index;
    
    if (boost::edge(map_.vFromIndex(this_index), map_.vFromIndex(target_index), map_.map).second || boost::edge(map_.vFromIndex(target_index), map_.vFromIndex(this_index), map_.map).second) {
      x_read = target_x;
      y_read = target_y;
      
      map_.map[target_index].probEmpty = 0.7;
      map_.updateMap(target_x, target_y);
    }
    else {
      map_.map[target_index].probTaken = 0.9;
      map_.updateMap(target_x, target_y);
      
      break;
    }
    
    ray_distance = vecMagnitude(ray_x, ray_y);
  }
}


int localize(const int direction) {
  int new_direction = direction;
  
  while(new_direction >= 360) {
    new_direction -= 360;
  }
  
  while(new_direction < 0) {
    new_direction += 360;
  }
  
  return new_direction;
}

float toRadians(const int degrees) {
  return (float) degrees * pi / 180.0f;
}

float vecMagnitude(const float x, const float y) {
  return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

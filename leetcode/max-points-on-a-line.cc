/*
 * Copyright 2017 All Rights Reserved.
 * Author: soygrow
 *
 * max-points-on-a-line.cc
 * ---------------------------------------------------------------------------
 * Given n points on a 2D plane, find the maximum number of points that lie 
 * on the same straight line.
 * ---------------------------------------------------------------------------
 */


#include <iostream>
#include <vector>
#include <map>
#include <algorithm>

#include "glog/logging.h"

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int a, int b) : x(a), y(b) {}
};


int gcd(int a, int b) {
  return (b == 0) ? a : gcd(b, a % b);
}

int maxPoints(std::vector<Point> &points) {
  if (points.size() < 3) {
    return points.size();
  }

  int res = 0;
  for (size_t i = 0; i < points.size(); i ++) {
    int duplicates = 1;
    Point x = points[i];
    std::map<std::pair<int, int>, int> points_line;
    
    for (size_t j = i+1; j < points.size(); j ++) {
      Point y = points[j];

      if (x.x == y.x && x.y == y.y) {
        duplicates ++;
        continue;
      }

      int delta_x = y.x - x.x;
      int delta_y = y.y - x.y;
      int gcd_x_y = gcd(delta_x, delta_y);
      points_line[{delta_x/gcd_x_y, delta_y/gcd_x_y}] ++;
    }

    res = std::max(res, duplicates);
    for (auto ite = points_line.begin(); ite != points_line.end(); ite ++) {
      res = std::max(res, ite->second + duplicates);
    }
  }

  return res;
}

/*
int maxPoints(std::vector<Point>& points) {
  int len = points.size();
  if(len< 2)
    return len;
  int res = 0;
  for(int i=0;i<len;i++) {
      std::map<std::pair<int,int>,int> slopeMap;
      int duplicates = 1;
      for(int j=i+1;j<len;j++) {
        if(points[i].x == points[j].x && points[i].y == points[j].y) {
          duplicates++;
          continue;
        }
        int dix = points[j].x - points[i].x;
        int diy = points[j].y - points[i].y;
        int maxD = gcd(dix,diy);
        slopeMap[{dix/maxD,diy/maxD}] ++;
      }
      res = std::max(res,duplicates);
      for(auto it=slopeMap.begin();it!=slopeMap.end();it++) {
        res = std::max(res,it->second + duplicates);
      }
    }
  return res;
}
*/
int main(int argc, char** argv) {
  std::vector<Point> vec_point;
  Point p1(1,1);
  Point p2(1,1);
  Point p3(1,1);
  Point p4(0,3);
  Point p5(1,4);
  vec_point.push_back(p1);
  vec_point.push_back(p2);
  vec_point.push_back(p3);
  //vec_point.push_back(p4);
  //vec_point.push_back(p5);

  std::cout << maxPoints(vec_point) << std::endl;
  return 0;
}

# Feb 7
We talked about timing a lot and doing odom by position vs velocity

for(auto & x: myvector)

for (const auto & x : myvector)
if it's large and you don't modify it


## DONT DO THIS
double x;
int y;

do const auto 




## LOCALIZATION AND MAPPING
* ancient maps :,) carved on bones
* polynesian waves
* theseus and the minotaur
* lighthouse
* magnetic compass in ancient china
* sun stone
* christopher columbus
* star based
* longitude: Greenwich England
* radio based first started in 1888!! eventually GPS :)

### Lots of these boil down to TRIANGULATION
* bearing ony measurements

### Example: we are in a boat in lake michigan
* get points of interest. Measure the angle to it.

## Autonomous Navigation
* Mapping + Localization + Motion Planning
* Slam doesn't really focus on the motion planning


## Localizaation
* Where am I? (relative to what?)
* We are given a map

## Mapping
* Where is everything given my location?
* Cartography

## Motion Planning
* How do I get there?
  * RRT
  * Probabilistic Road map
  * Potential Fields
  * Many Others


## SLAM
* I don't know where I am and I don't have a map
  * That's scary!!
* Try it at home?
* "Maybe if you're a social person and not an engineer you can ask someone"
* "The lowest form of papers is research about research"

## PAPERS
* First started talking about it is around 1988
* "Solved" in 2001
* But there's a parallel track in CV land. 
  * VO: Visual Odometry: How did I move, given only images
  * SFM: Structure from Motion: Where is camera relative to 3d points?


## Basic Slaam
* Online SLAM
  * Estimate probability distribution of our current pose and the map, given measurements and control inputs
  * runs in real time
* Full SLAM (offline)
  * estimate entire trajectory and map given measurements and control inputs
  * retrospective!

## MAP 
* Feature based map
  * sparse landmarks arbitrarily placed eg some cylinders
* Grid based map
  * space divided into cells with some probability of occupancy

## METHODS
* Kalman filter, particle filter, fast slam, graph slam, visual slam
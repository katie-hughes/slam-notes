# Feb 2 Notes

Frame w, frame b

Frame p: aligned with the world located at the body.


$V_p = A(\theta, 0, 0) V_b$

$V_p = Ad_{T_{pb}}V_b$

Body twist input for IK is in frame b NOT frame p.



OR: integrate twist to go from b to b'. Get Tbb'. Then do Twb' = Twb*Tbb'. 






START OVER LOOOOL

Twist Vb

Displacement Tbb' by integrating 

TwbTbb' = Twb'

Lots of matrices though

Tbb' = T(delta theta, delta x, delta y)

extract and put this into delta qb

## other stuff
* run commands and end up with aarch64
* contains cross compiling argument. mounts worksapace inside docker container
* run `./aarch64 colcon_aarch64`
* run `./aarch64 bash`: to go inside docker container.this is what's on the raspberry pi.
* `rsync -av --delete aarch64_install msr@bebop:/home/msr/install`
* `ssh -oSendEnv=ROS_DOMAIN_ID msr@bebop`
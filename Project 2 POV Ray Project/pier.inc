#include "colors.inc"
#include "textures.inc"
#include "woods.inc"

camera {
  location  <0.0, 2, -5.0>
  look_at   <0.0, 1,  0.0>
}       

background {
	rgb <0.85,0.95,1>
}
          
#declare R = 0.20; //radius                              

union{    
    box {
    	<0,0,0>, <3,0.5,10> 
    	texture {T_Wood7}
    	translate <-1.5, 0,-1.2>
    }      
    // 4 in z direction
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <2.6, -.3, 0>
    }     
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <2.6, -.3, 3>
    }
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <2.6, -.3, 6>
    }
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <2.6, -.3, 9>
    }
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <-.3, -.3, 0>
    }
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <-.3, -.3, 3>
    }
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <-.3, -.3, 6>
    }
    cylinder {
        <-1,-1,-1>,<-1, 1,-1>,R
        translate <-.3, -.3, 9>
    }
    texture{T_Wood7}     
}
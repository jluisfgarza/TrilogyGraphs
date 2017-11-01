// Author: Trilogy Graphs
// Date: November 1, 2017
//
#include "colors.inc"
#include "functions.inc"
#include "metals.inc"
#include "textures.inc"
#include "palm1.inc"
#include "palm2.inc"

camera {
  location  <0.0, 2, -5.0>
  look_at   <0.0, 1,  0.0>
}


//——————————————————————————————————————————————————
//——————————————————————————————————————————————————

// Scene Creation

//——————————————————————————————————————————————————
//——————————————————————————————————————————————————
                     
// Radiosity (global illumination) settings
global_settings {
        radiosity {
            pretrace_start 0.04           // start pretrace at this size
            pretrace_end   0.02           // end pretrace at this size
            count 100                     // higher -> higher quality (1..1600) [35]
            nearest_count 7               // higher -> higher quality (1..10) [5]
            error_bound 1.8               // higher -> smoother, less accurate [1.8]
            recursion_limit 1             // how much interreflections are calculated (1..5+) [3]
            low_error_factor .5           // reduce error_bound during last pretrace step
            gray_threshold 0.0            // increase for weakening colors (0..1) [0]
            minimum_reuse 0.015           // reuse of old radiosity samples [0.015]
            brightness 1                  // brightness of radiosity effects (0..1) [1]

            adc_bailout 0.01/2
        }  
}
/*
//——————————————————————————————————————————————————

// Camera settings
#declare C_LOC = <0, 0, 0>;

// perspective (default) camera
camera {
  location  C_LOC
  //look_at   <0.0, 0.0,  0.0>    
  //angle     40
}      

//——————————————————————————————————————————————————
   */
// Light sources
light_source { <3.5, 10, 0>, 1 }

//——————————————————————————————————————————————————

// Sky

sky_sphere {
    pigment {
        function { max(min(y,1),0) }
        color_map {
            [  0/269 color rgb <120/255, 79/255, 51/255>]
            [  1/269 color rgb <141/255, 83/255, 46/255>]
            [  2/269 color rgb <177/255, 86/255, 41/255>]
            [  3/269 color rgb <235/255,128/255, 72/255>]
            [  5/269 color rgb <255/255,159/255, 72/255>]
            [  8/269 color rgb <255/255,203/255, 94/255>] // New
            [ 10/269 color rgb <255/255,218/255,112/255>]
            [ 13/269 color rgb <255/255,233/255,148/255>] // New
            [ 15/269 color rgb <251/255,241/255,172/255>] // New
            [ 20/269 color rgb <255/255,246/255,203/255>]
            [ 30/269 color rgb <255/255,240/255,219/255>]
            [ 40/269 color rgb <236/255,223/255,214/255>]
            [ 50/269 color rgb <205/255,204/255,212/255>]
            [ 55/269 color rgb <185/255,190/255,209/255>] // New
            [ 60/269 color rgb <166/255,176/255,201/255>]
            [ 65/269 color rgb <149/255,163/255,190/255>] // New
            [ 70/269 color rgb <129/255,149/255,182/255>]
            [ 80/269 color rgb <103/255,127/255,171/255>]
            [ 90/269 color rgb < 79/255,110/255,154/255>]
            [100/269 color rgb < 66/255, 97/255,143/255>]
            [110/269 color rgb < 52/255, 84/255,131/255>]
            [120/269 color rgb < 47/255, 75/255,122/255>]
            [140/269 color rgb < 37/255, 60/255,102/255>]
            [160/269 color rgb < 32/255, 51/255, 84/255>]
            [180/269 color rgb < 27/255, 42/255, 71/255>]
            [200/269 color rgb < 25/255, 36/255, 58/255>]
            [220/269 color rgb < 22/255, 31/255, 48/255>]
            [240/269 color rgb < 18/255, 27/255, 42/255>]
            [260/269 color rgb < 15/255, 21/255, 33/255>]
            [269/269 color rgb < 15/255, 21/255, 33/255>]
        }
    }
    scale (1/2)
    
    
}

/*
plane{<0,1,0>, 0 
      texture{pigment{ rgb <0.2, 0.2, 0.2> } 
              normal { bumps 0.08 scale <1,0.25,0.35>*1 turbulence 0.6 }
              finish { ambient 0.05 diffuse 0.55 
                       brilliance 6.0 phong 0.8 phong_size 120
                       reflection 0.6 }
             }
     }*/

plane {
    y, 0.0
    material {
        texture {
            pigment {
                color rgbt <0.8, 0.9, 1, 0.9>
            }
            finish {
                ambient 0.0
                diffuse 0.0

                reflection {
                    0.2, 1.0
                    fresnel on
                }

                specular 0.4
                roughness 0.003
            }
            normal {
                function {
                    f_ridged_mf(x/9, y, z/5, 0.1, 3.0, 7, 0.7, 0.7, 2)
                } 0.6
                turbulence 2.5
                scale 0.13
            }
        }
        interior { ior 1.3 }
    }
}

plane {
    y, 0.0 
    translate <0, -0.01, 0>
}

// Declaration of the cloud-form pigment
#declare P_Cloud = pigment {
    wrinkles
    turbulence <0.2, 0.2, 0.2>
    octaves    7
    omega      0.8
    lambda     3
    color_map {
        [0.00 color rgbt <1.00,1.00,1.00,1.00>]
        [0.50 color rgbt <1.00,1.00,1.00,1.00>]
        [0.60 color rgbt <0.50,0.50,0.50,0.50>]
        [1.00 color rgbt <1.00,1.00,1.00,0.00>]
    }
    scale <12000,12000,12000>
}
/*
// Unification of several planes to give a clouded sky plane
union {
    plane {
        <0, -1, 0> 0
        texture {
            pigment { P_Cloud }
            finish { ambient 1.0 }
        }
    }

    plane {
        <0, -1, 0> 0
        translate <0, 5, 0>
        texture {
            pigment { P_Cloud }
            finish { ambient 0.6 }
        }
    }

    plane {
        <0, -1, 0> 0
        translate <0, 10, 0>
        texture {
            pigment { P_Cloud }
            finish { ambient 0.8 }
        }
    }

    plane {
        <0, -1, 0> 0
        translate <0, 15, 0>
        texture {
            pigment { P_Cloud }
            finish { ambient 0.4 }
        }
    }
    translate <0, 1000, 0>
}

*/

plane {
        <0, -1, 0> 0
        translate <0, 1200, 0>
        texture {
            pigment { P_Cloud }
            finish { ambient 0.4 }
        }
    }
 /*   
    // a mirror sphere !!!!  
sphere{ <0,0,0>,0.4 scale <1,1,1> rotate<0,0,0> translate<0,0.7,0>
        texture{ Polished_Chrome }
      }*/

/*
object {
	box {4,4}
	translate <0,0,0>
	texture{
		pigment{
			rgb(1,1,1)
		}
	}
}*/


#declare hftext= function{
	pigment{
		image_map{
			tga
			"sample" 
			map_type 1 
			interpolate 3
		}
	}
}

#declare FelbriggSand = texture {
 pigment {color rgb < 1, 0.9, 0.65>}
 normal {granite 0.2 scale 0.02}
 normal { bumps 0.4 scale 4}
 finish {
  	brilliance 1.6
  	specular 0.3
  	ambient 0.05
 }
}


// Now the isosurface
#declare rs=0.1; // try several rs values <1; the higher it is the higher is the text
#declare hfsphere = isosurface{
        function{f_sphere(x,y,z, 1) + rs- hftext(x,y,z).gray*rs}
        contained_by{sphere{0,1}}
        max_gradient 120 // <--- important- adjust to your picture otherwise strange things happen
        texture{FelbriggSand}        
}

object {
	hfsphere
	translate <0, -0.2, 0>
	scale <3.5,1,1>
}

//PALMS

#declare LEAVES = object {
    palm_13_leaves
    pigment { color rgb <0, 0.9, 0> }
}

#declare STEMS = object {
    palm_13_stems
    pigment { color rgb <144/255, 104/255, 78/255> }
}

#declare PALM = union {
    object { LEAVES }
    object { STEMS }
}
 
 object {PALM
	scale <0.2, 0.2, 0.2>
	translate <2, 0, 0>
 }
 
  object {PALM
	scale <0.2, 0.2, 0.2>
	translate <2, -1, -0.6>
 }
 
  object {PALM
	scale <0.2, 0.2, 0.2>
	translate <0.9, 0, 1>
 }
 
   object {PALM
	scale <0.2, 0.2, 0.2>
	translate <1.2, 0, -0.5>
 }
 
 object {PALM
	scale <0.2, 0.2, 0.2>
	translate <1.2, 0, -0.8>
 }
 
object {PALM
	scale <0.2, 0.2, 0.2>
	translate <0, 0, 0>
 }

 
 object {PALM
	scale <0.2, 0.2, 0.2>
	translate <0.3, 0, -0.5>
 }
 
  object {PALM
	scale <0.2, 0.2, 0.2>
	translate <-0.8, 0, -0.4>
 }
 
  object {PALM
	scale <0.2, 0.2, 0.2>
	translate <-0.5, -1, 0>
 }
 
 object {PALM
	scale <0.2, 0.2, 0.2>
	translate <-1.5, 0, 1>
 }
 
  object {PALM
	scale <0.2, 0.2, 0.2>
	translate <-1.5, 0, -0.7>
 }
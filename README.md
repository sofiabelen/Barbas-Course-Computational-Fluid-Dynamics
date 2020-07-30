# Computational Fluid Dynamics

My code for the Computational Fluid Dynamics course by Prof. Lorena A. Barba, from Boston University

Check out the course: https://www.youtube.com/watch?v=cDy5XGOokBY&list=PL30F4C5ABCE62CB61&index=1

## Assigment #1: 1D Linear Convection
**Discretization scheme:**
1. Forward difference for the time derivative.
2. Backward difference for the space derivative.

![hippo](Images/1-exp18.gif)
![Alt text](Images/assigment1-3d.svg?raw=true "1")

### When the consistency condition is not satisfied, in this case: the CFL number is greater than or equal to 0 and less than or equal to 1, our solution will diverge.

![hippo](Images/1-exp31.gif)
![Alt text](Images/assigment1-3d-diverges.svg?raw=true "1")

## Assignment #2: 1D Non-linear Convection
**Discretization scheme:**
1. Forward difference in time.
2. Backward difference in space.

![hippo](Images/2-exp27.gif)
![Alt text](Images/assigment2-3d.svg?raw=true "2")

## Assignment #3: 1D Diffusion
**Discretization scheme:**
1. Forward difference in time.
2. Central difference in space. (Since space is isotropic).

![hippo](Images/3-exp16.gif)
![Alt text](Images/assigment3-3d.svg?raw=true "3")

### When the Von Neumann stability condition is not met, in this case: CFL number is less than or equal to 0.5, the solution diverges. (Will write more on this later).

![hippo](Images/3-exp29.gif)
![Alt text](Images/assigment3-3d_diverges.svg?raw=true "3 diverges")

## Assignment #4: 1D Burgers' Equation

![Alt text](Images/assigment4.svg?raw=true "4")

## Assignment #5: 2D Linear Convection
**Discretization scheme:**
1. Forward difference for the time derivative.
2. Backward difference for the space derivatives.

![Alt text](Images/assigment5.svg?raw=true "5")

## Assignment #6: 2D Convection

![Alt text](Images/assigment6.svg?raw=true "6")

## Assignment #7: 2D Diffusion

![Alt text](Images/assigment7.svg?raw=true "7")

## Assignment #8: 2D Diffusion

![Alt text](Images/assigment8.svg?raw=true "8")

## Assignment #9: Laplace Equation

![hippo](Images/9-exp54.gif)

## Assignment #10: Poisson Equation

![hippo](Images/10-exp59.gif)

## Assignment #11: Cavity Flow with Navier-Stokes

![Alt text](Images/11-exp121.svg?raw=true "11")

## Assignment #12: Channel Flow with Navier-Stokes

![Alt text](Images/12-exp133.svg?raw=true "12")

PROGRAM formatlearn
	IMPLICIT NONE
        
	real x, y,z ,a
	
	x =  45.4077072
	y = 0.701794088
	z = 175.855865
	a = -0.586750627
	
	write(*, 100) x,y,z,a

100 format (F6.2,"," F5.3,"," F6.2,"," F5.3)
        
END PROGRAM formatlearn

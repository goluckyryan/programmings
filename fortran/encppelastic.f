     
SUBROUTINE encppelastic(val,nx,ny,naok,analyzer)
      IMPLICIT NONE

      INCLUDE '../core/analyslogic.fh'
c      include '../sharaq/shrq_s0info.fh'
      INCLUDE '../traj/trajectory.fh'
c      include '../optics/optics.fh'
c      include 'physprm.fh'

      INTEGER analyzer
      INTEGER nx,ny,naok
      REAL val(nx,ny)


      REAL c , mp, deg, rad
      PARAMETER (c=299792458,mp=938.272046, 180.0/ACOS(-1.0), ACOS(-1.0)/180.0)
      REAL p1f(3), p2f(3), t1(3), t2(3)
      REAL T, theta_NN, beta1, beta2, tof1, tof2
      INTEGER	i
      REAL temp, temp2


      IF (initencflag(analyzer)) THEN
         WRITE(*,*) ' ANAPAW-M : ivmr analysis = ',analyzer
         CALL srand(time())
         initencflag(analyzer) = .FALSE. 
      END IF


      naok = 0
       
      naok = naok + 1 
      Val(1,naok) = 100

c putting the data from Traj to Val
      Val(8,naok) = 
      Val(9,naok) =
      Val(10,naok) = 
      
c put the data to t1, generate p1 and p2, then given t2. 


        t1(1) =  
        t1(3) =
        
        t1(3)=t1(3)*rad
        t1(2) = sqrt(2*mp*t1(1)+(t1(1))**2)
        CALL MakeVector(t1,p1f)
        
        temp  = tan(t1(3))**2
        temp2 = 2*mp-t1(1)*temp
        T     = (2*t1(1)*mp*(1+temp))/temp2
        theta_NN = atan(sqrt(((t1(1)+2*mp)*temp)/temp2))*2
        
        
        p2f(1)=mp+T*(sin(theta_NN/2))**2
        p2f(2)=-sqrt(mp*T/2)*sin(theta_NN)
        p2f(3)=sqrt(2*mp*T+T**2)*(sin(theta_NN/2))**2

        
        CALL KinPara(p1f, t1)
        CALL KinPara(p2f, t2)
        beta1 = beta(p1f)
        beta2 = beta(p2f)
        tof1  = TOF(t1(3),beta1)
        tof2  = TOF(t2(3),beta2)
        
c	campare the conincident event, check the fillment of the elastics kinematics
	IF ( ) THEN{		
c	if the result is positive, save to Val
c		Val(1,naok) is the LMWDC data
		Val(11, naok) =        
c		Val(2,naok) is the RMWDC data
		Val(12, naok) = 
c		Val(3, naok) is the sumMWDC data
		Val(13, naok) = 
c		Val(4, naok) is the DiffMWDC data
       		Val(14, naok) = 
c		Val(5, naok) is the Uncertaintly data
        	val(15, naok) =
	}ELSE {
		Val(11, naok) = 0       
		Val(12, naok) = 0
		Val(13, naok) = 0
       		Val(14, naok) = 0
        	val(15, naok) = 0
	}
	
c	start of subroutines
c************************************************************************
        SUBROUTINE KinPara (p, t)
        	IMPLICIT NONE
        	
        	REAL, INTENT(IN), DIMENSION(3)	:: p
       		REAL, INTENT(OUT), DIMENSION(3)	:: t
       		t(2)=sqrt(p(2)**2+p(3)**2)
       		t(1)=p(1)-mp
       		t(3)=atan2(p(2),p(3))*180/pi
        	
       	END SUBROUTINE KinPara
        
       	SUBROUTINE MakeVector (t, p)
       		IMPLICIT NONE
       	
       		REAL, INTENT(IN), DIMENSION(3)	:: t
       		REAL, INTENT(OUT), DIMENSION(3)	:: p
       		p(1)=mp+t(1)
       		p(2)=t(2)*sin(t(3))
       		p(3)=t(2)*cos(t(3))
        	
       	END SUBROUTINE MakeVector
	
	REAL FUNCTION beta(p)
		IMPLICIT NONE
		
		REAL, INTENT(IN), DIMENSION(3)	:: p
		beta = sqrt(p(2)**2+p(3)**2)/p(1)
			
	END FUNCTION beta
	
	REAL FUNCTION TOF(angle, beta)
		IMPLICIT NONE
			
		REAL, INTENT(IN)	:: angle, beta
		REAL			:: distance
			
		distance = 1.146/cos(abs(angle*pi/180)-pi/3)	
		TOF = distance/beta/c*1e+9
			
	END FUNCTION TOF
c	end of subroutines
c************************************************************************


      return
      end 



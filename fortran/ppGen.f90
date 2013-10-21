PROGRAM ppelasticExp
	IMPLICIT NONE
        
        DOUBLE PRECISION, PARAMETER	:: pi = ACOS(-1.0)
        REAL, PARAMETER			:: mp=938.272046 , c=299792458.0
        REAL, DIMENSION(3)		:: p1f, p2f, t1, t2
        REAL				:: T, theta_NN, beta1, beta2, tof1, tof2
        INTEGER				:: i

        WRITE(*,*) " K.E theta_NN = "
        READ(*,*)  T, theta_NN
        
        theta_NN=theta_NN*pi/180
        ! incident proton
        p1f(1)=mp+T*(cos(theta_NN/2))**2
        p1f(2)=sqrt(mp*T/2)*sin(theta_NN)
        p1f(3)=sqrt(2*mp*T+T**2)*(cos(theta_NN/2))**2
        
        p2f(1)=mp+T*(sin(theta_NN/2))**2
        p2f(2)=-sqrt(mp*T/2)*sin(theta_NN)
        p2f(3)=sqrt(2*mp*T+T**2)*(sin(theta_NN/2))**2

        WRITE(*,*) "p1f :",(p1f(i), i=1, 3)
        WRITE(*,*) "p2f :",(p2f(i), i=1, 3)
        
        CALL KinPara(p1f, t1)
        CALL KinPara(p2f, t2)
        beta1 = beta(p1f)
        beta2 = beta(p2f)
        tof1  = TOF(t1(3),beta1)
        tof2  = TOF(t2(3),beta2)
        
        WRITE(*,*) "-----Kinetic (T, p, theta, beta)-------"
        WRITE(*,*) "p1f :",(t1(i), i=1, 3), beta1
        WRITE(*,*) "p2f :",(t2(i), i=1, 3), beta2
        
        WRITE(*,*) "---------------------------------"
        WRITE(*,*) "opening angle =", t1(3)-t2(3)
        WRITE(*,*) "Time of Fligth"
        WRITE(*,*) "p1f", tof1, "ns"
        WRITE(*,*) "p2f", tof2, "ns"
        WRITE(*,*) " time diff :", abs(tof1-tof2), "ns"
         
        

CONTAINS !all subroutines also start with Capital letter
        SUBROUTINE KinPara (p, t)
        	IMPLICIT NONE
        	
        	REAL, INTENT(IN), DIMENSION(3)	:: p
        	REAL, INTENT(OUT), DIMENSION(3)	:: t
        	t(2)=sqrt(p(2)**2+p(3)**2)
        	t(1)=p(1)-mp
        	t(3)=atan2(p(2),p(3))*180/pi
        	
        END SUBROUTINE KinPara
	
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
	
      
        
END PROGRAM ppelasticExp

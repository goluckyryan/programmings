PROGRAM savepp
	IMPLICIT NONE
        
        DOUBLE PRECISION, PARAMETER	:: pi = ACOS(-1.0)
        REAL, PARAMETER			:: mp=938.272046 , c=299792458.0
        REAL, DIMENSION(3)		:: p1f, p2f, t1, t2
        REAL				:: T, theta_NN, beta1, beta2, tof1, tof2
        INTEGER				:: i, T1_loop, theta_1_loop, num
        REAL				:: temp, temp2
        INTEGER				:: T1_start, T1_stop, theta_1_start, theta_1_stop

        WRITE(*,*) " T1_start T1_stop theta_1_start theta_1_stop = "
        READ(*,*) T1_start, T1_stop, theta_1_start, theta_1_stop
        
        DO T1_loop=T1_start, T1_stop, 1
        DO theta_1_loop = theta_1_start, theta_1_stop, 1
        num=num+1
        t1(1) = T1_loop
        t1(3) = theta_1_loop*pi/180
        t1(2) = sqrt(2*mp*t1(1)+(t1(1))**2)
        CALL MakeVector(t1,p1f)
        
        temp  = tan(t1(3))**2
        temp2 = 2*mp-t1(1)*temp
        T     = (2*t1(1)*mp*(1+temp))/temp2
        theta_NN = atan(sqrt(((t1(1)+2*mp)*temp)/temp2))*2
        
        !WRITE(*,*) "incident K.E. :", T, "CM angle :", theta_NN*180/pi
        
        p2f(1)=mp+T*(sin(theta_NN/2))**2
        p2f(2)=-sqrt(mp*T/2)*sin(theta_NN)
        p2f(3)=sqrt(2*mp*T+T**2)*(sin(theta_NN/2))**2

        !WRITE(*,*) "p1f :",(p1f(i), i=1, 3)
        !WRITE(*,*) "p2f :",(p2f(i), i=1, 3)
        
        CALL KinPara(p1f, t1)
        CALL KinPara(p2f, t2)
        beta1 = beta(p1f)
        beta2 = beta(p2f)
        tof1  = TOF(t1(3),beta1)
        tof2  = TOF(t2(3),beta2)
        
        !WRITE(*,*) "-----Kinetic (T, p, theta, beta)-------"
        !WRITE(*,*) "p1f :",(t1(i), i=1, 3), beta1
        !WRITE(*,*) "p2f :",(t2(i), i=1, 3), beta2
        
        !WRITE(*,*) "---------------------------------------"
        !WRITE(*,*) "opening angle =", t1(3)-t2(3)
        !WRITE(*,*) "Time of Fligth"
        !WRITE(*,*) "p1f", tof1, "ns"
        !WRITE(*,*) "p2f", tof2, "ns"
        WRITE(*,*) " time diff :", abs(tof1-tof2), "ns", num
        
        !file I/O
        OPEN(1, FILE="test.txt", ACCESS="APPEND") ! ACCESS type are , "APPEND", "DIREC", "SEQUENTIAL"(default)
        WRITE(1,2) t1(1), t1(3), t2(1), t2(3), T, theta_NN*180/pi, abs(tof1-tof2)
        CLOSE(1)
2	FORMAT (11f10.4)
        END DO
        END DO

CONTAINS !all subroutines also start with Capital letter
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
	       
END PROGRAM savepp

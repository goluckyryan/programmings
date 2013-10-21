PROGRAM knockout
	IMPLICIT NONE
        
        REAL, PARAMETER         :: pi = ACOS(-1.0), mp=981.2 , mn=999.21 !constant declaration
        INTEGER                 :: MA
        !REAL		        :: TiL, k, theta_k, phi_k, S
        REAL, DIMENSION(5)      :: Para
        REAL, DIMENSION(4)      :: pAL, pkL, p1L, p2L
        REAL, DIMENSION(4)      :: pA, pk, p1, p2
        REAL, DIMENSION(4)      :: pAC, pkC, p1C, p2C
        REAL, DIMENSION(4)      :: pc, t 
        INTEGER	                :: i

        WRITE(*,*) "MA K.E. k theta_k phi_k S = "
        READ(*,*) MA, (Para(i), i=1, 5)

        ! in oxygen frame
        pAL(1)= mp
        pAL(2)= 100
        pAL(3)= 90
        pAL(4)= 0


        CALL Make4momentum(pAL)
        
        WRITE(*,*) (pAL(i), i=1, 4)

        CALL Momentum(pAL, t)

        WRITE(*,*) (t(i), i=1, 4)

        OPEN (1, FILE="test.txt" )

        WRITE(1,2) (t(i), i=1, 4)
	CLOSE(1)
2 	FORMAT (es14.4, es14.4, es14.4, es14.4)

CONTAINS !all subroutines also start with Capital letter
	SUBROUTINE Make4momentum(p) ! the imput is (mass, momentum, theta, phi)
                IMPLICIT NONE

                REAL, INTENT(INOUT), DIMENSION(4) :: p
                REAL, DIMENSION(4) :: temp
                INTEGER :: i
                DO i = 1, 2
                	temp(i) = p(i)
                END DO
                temp(3)=p(3)*pi/180
                temp(4)=p(4)*pi/180
                p(1)=SQRT(temp(1)**2+temp(2)**2)
                p(2)=temp(2)*SIN(temp(3))*COS(temp(4))
                p(3)=temp(2)*SIN(temp(3))*SIN(temp(4))
                p(4)=temp(2)*COS(temp(3))                
                
        END SUBROUTINE Make4momentum
        
	SUBROUTINE Make4KE(p) ! the imput is (mass, KE, theta, phi)
                IMPLICIT NONE

                REAL, INTENT(INOUT), DIMENSION(4) :: p
                REAL, DIMENSION(4) :: temp
                REAL    :: momentum
                INTEGER :: i
                DO i = 1, 2
                	temp(i) = p(i)
                END DO
                temp(3)=p(3)*pi/180
                temp(4)=p(4)*pi/180
                p(1)=temp(1)+temp(2)
                momentum = SQRT(p(1)**2-temp(1)**2)
                p(2)=momentum*SIN(temp(3))*COS(temp(4))
                p(3)=momentum*SIN(temp(3))*SIN(temp(4))
                p(4)=momentum*COS(temp(3))                
                
        END SUBROUTINE Make4KE
        
        SUBROUTINE Momentum(p, t)
                IMPLICIT NONE

                REAL, INTENT(IN), DIMENSION(1:4) :: p
                REAl, INTENT(OUT), DIMENSION(1:4):: t
                REAL             :: mass
                t(2)=SQRT(p(2)**2+p(3)**2+p(4)**2)
                mass = SQRT((p(1))**2-(t(2))**2)
                t(1)=p(1)-mass
                t(3)=ATAN2(SQRT(p(2)**2+p(3)**2), p(4))*180/pi
                t(4)=ATAN2(p(3),p(2))*180/pi
                
        END SUBROUTINE Momentum

        SUBROUTINE Lorentz(p, t)
                IMPLICIT NONE

                REAL, INTENT(IN), DIMENSION(1:4) :: p
                REAl, INTENT(OUT), DIMENSION(1:4):: t
                REAL             :: mass
                t(2)=SQRT(p(2)**2+p(3)**2+p(4)**2)
                mass = SQRT(p(1)**2-t(2)**2)
                t(1)=p(1)-mass
                t(2)=ATAN2(SQRT(p(2)**2+p(3)**2), p(4))*180/pi
                t(3)=ATAN2(p(3),p(2))*180/pi
                
        END SUBROUTINE Lorentz
        
END PROGRAM knockout

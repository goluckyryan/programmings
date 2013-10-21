cABOTBODY3. RELATIVISTIC KINEMATICS FOR THREE-BODY FINAL STATES.
c1   BRAITHWAITE, W.J.
cREF. IN COMP. PHYS. COMMUN. 4 (1972) 233
c// JOB J5B WJB D8367.CYCLO    T=.15  N=BODY3
c// EXEC FORTGCLG
c//FORT.SYSIN DD *
C     THREE BODY KINEMATICS USING A THREE DIMENSIONAL TWO BODY CODE.
C
      IMPLICIT REAL*8 (A-H,O-Z)
      DIMENSION UX(3),UY(3),UZ(3),P2X(2),P2Y(2),P2Z(2),P3X(2),P3Y(2)
     1,P3Z(2),TH(3),PH(3),T2(2),T3(2),TH3(2),PH3(2),E13(2),E12(2)
     2,ID(20)
      DATA C/11.802854/, CC/.1745329251994330D-01/, CK/931.441D0/
C
  100 READ(5,1)ID
      READ(5,2)AI,A1,A2,A3
      READ(5,2)T1L,T1U,DT1,TH(1),PH(1),T120,R2,R1
  110 READ(5,2,end=1000)TI,Q,TH(2),TH(3),PH(2),PH(3)
      IF(TI) 100,100,120
  120 T1=DMAX1(T1L,1.D-30)
      WI=CK*AI
      W1=CK*A1
      W2=CK*A2
      W3=CK*A3
      WT=W1+W2+W3-WI+Q
      WRITE(6,10)ID,TI,AI,A1,A2,A3,Q,TH(2),PH(2),TH(3),PH(3)
      WRITE(6,11)
      DO 130 I=1,3
      UX(I)=DCOS(CC*PH(I))*DCOS(CC*TH(I))
      UY(I)=DCOS(CC*PH(I))*DSIN(CC*TH(I))
  130 UZ(I)=DSIN(CC*PH(I))
      PI =DSQRT(TI*(TI+2.*WI))
      PIX=PI*UX(1)
      PIY=PI*UY(1)
      PIZ=PI*UZ(1)
  140 P1 =DSQRT(T1*(T1+2.*W1))
      P1X=P1*UX(2)
      P1Y=P1*UY(2)
      P1Z=P1*UZ(2)
      P2X(1)=UX(3)
      P2Y(1)=UY(3)
      P2Z(1)=UZ(3)
      CALL TWOBOD(PIX-P1X,PIY-P1Y,PIZ-P1Z,TI+WI+WT-T1-W1,P2X,P2Y,P2Z,W2,
     1            P3X,P3Y,P3Z,W3,N)
      IF(N.LE.0) GO TO 220
      DO 160 I=1,N
      P2   =DSQRT(P2X(I)**2+P2Y(I)**2+P2Z(I)**2)
      T2(I)=DSQRT(P2*P2+W2*W2)-W2
      T3(I)=DSQRT(P3X(I)**2+P3Y(I)**2+P3Z(I)**2+W3*W3)-W3
      TH3(I)=DATAN2(P3Y(I),P3X(I))/CC
      PH3(I)=DATAN2(P3Z(I),DSQRT(P3X(I)**2+P3Y(I)**2))/CC
      E13(I)=DSQRT((TI+WI+WT-T2(I)-W2)**2-(PIX-P2X(I))**2-(PIY-P2Y(I))**
     12          -(PIZ-P2Z(I))**2)-(W1+W3)
      E12(I)=DSQRT((TI+WI+WT-T3(I)-W3)**2-(PIX-P3X(I))**2-(PIY-P3Y(I))**
     12          -(PIZ-P3Z(I))**2)-(W1+W2)
      IF(R1+R2) 160,160,150
  150 T2(I)=T120+(((T2(I)+W2)/P2)*R2-((T1+W1)/P1)*R1)/C
  160 CONTINUE
      E23=DSQRT((TI+WI+WT-T1-W1)**2-(PIX-P1X)**2-(PIY-P1Y)**2
     1        -(PIZ-P1Z)**2)-(W2+W3)
      IF(N.EQ.2) GO TO 210
      T2(2)=0.D0
      T3(2)=0.D0
      TH3(2)=0.D0
      PH3(2)=0.D0
      E13(2)=0.D0
      E12(2)=0.D0
  210 WRITE(6,12)T1,T2(1),T3(1),T2(2),T3(2),E23,E13(1),E12(1),E13(2)
     1        ,E12(2),(TH3(I),PH3(I),I=1,2)
  220 T1=T1+DT1
      IF(T1-T1U) 140,140,110
 1000 CALL EXIT
    1 FORMAT(20A4)
    2 FORMAT(8F10.5)
   10 FORMAT(1H1,7X,20A4//8X,3HT0=,F6.3,11X,3HM0=,F6.3,10X,3HM1=,F6.3,
     110X,3HM2=,F6.3,10X,3HM3=,F6.3/8X,2HQ=,F7.3,11X,4HTH1=,F5.1,10X,
     24HPH1=,F5.1,10X,4HTH2=,F5.1,10X,4HPH2=,F5.1//)
   11 FORMAT(8X,2HT1,6X,3HT2+,6X,3HT3+,6X,3HT2-,6X,3HT3-,6X,3HE23,5X,
     14HE13+,5X,4HE12+,5X,4HE13-,5X,4HE12-,5X,4HTH3+,5X,4HPH3+,5X,4HTH3-
     2,5X,4HPH3-/)
   12 FORMAT(1X,10F9.3,4F9.2)
      END

      SUBROUTINE TWOBOD(P0X,P0Y,P0Z,E0,P1X,P1Y,P1Z,A1,P2X,P2Y,P2Z,A2,N)
C
      IMPLICIT REAL*8 (A-H,O-Z)
      DIMENSION P1X(2),P1Y(2),P1Z(2),P2X(2),P2Y(2),P2Z(2)
C
      P02=P0X*P0X+P0Y*P0Y+P0Z*P0Z
      P0 =DSQRT(P02)
      P1 =DSQRT(P1X(1)**2+P1Y(1)**2+P1Z(1)**2)
      PC =(P0X*P1X(1)+P0Y*P1Y(1)+P0Z*P1Z(1))/P1
      E02=E0*E0
      G  =(E02-P02-A2*A2+A1*A1)/2.D0
      A  =E02-PC*PC
      B  =G*PC
      C  =E02*A1*A1-G*G
      N=1
      IF(A) 110,100,110
  100 A=C/(2.D0*B*P1)
      IF(B) 500,800,500
  110 B=B/A
      C=B*B-C/A
      IF(C) 800,800,200
  200 C=DSQRT(C)
      A=(B-C)/P1
      IF(A) 400,400,300
  300 N=2
      P1X(2)=P1X(1)*A
      P1Y(2)=P1Y(1)*A
      P1Z(2)=P1Z(1)*A
      P2X(2)=P0X-P1X(2)
      P2Y(2)=P0Y-P1Y(2)
      P2Z(2)=P0Z-P1Z(2)
  400 A=(B+C)/P1
  500 IF(A) 800,800,600
  600 P1X(1)=P1X(1)*A
      P1Y(1)=P1Y(1)*A
      P1Z(1)=P1Z(1)*A
      P2X(1)=P0X-P1X(1)
      P2Y(1)=P0Y-P1Y(1)
      P2Z(1)=P0Z-P1Z(1)
  700 RETURN
  800 N=0
      GO TO 700
      END

c//GO.SYSIN DD *
C12(A,PN)N14(G.S.)
c4.        1.        1.        14.
c0.        22.       .2
c42.       -15.8     30.       30.
c/*

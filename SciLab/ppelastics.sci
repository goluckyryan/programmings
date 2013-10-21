// this is for pp elastic 
clear thet1List
n=10000;
for i=1:n
    thetaList(i)=SphericalDist(1);
    phiList(i)=SphericalDist(2);
end

clf()
histplot(20,thetaList) // histplot(bin,list)

mp=983.27203;
T=260;

p1i={mp+T,0,0,sqrt(2*mp*T+T**2)};
p2i={mp,0,0,0};
rel_beta=p1i(4)/(p1i(1)+p2i(1))
p1ic=Lz4D(-rel_beta)*(p1i');
p2ic=Lz4D(-rel_beta)*(p2i');
Loren=Lz4D(rel_beta);

for i=1:n
    G1=Rot4D({0,1,0},thetaList(i));
    G2=Rot4D({0,0,1},phiList(i));
    p1fc=G2*G1*p1ic;
    p1f=Loren*p1fc;
  
    //p2fcList(i)=Rotz(phiList(i))*Roty(thetaList(i))*(p2ic);

    //p2fList(i)=Lz4D(rel_beta)*p2fcList(i);
    ke1List(i)=KE(p1f,mp);
    //ke2List(i)=KE(p2fList(i),mp);
    temp=polarangle4D(p1f);
    thet1List(i)=temp(2);
    //thet2List(i)=polarangle4D(p2fList(i));
end

clf()
histplot(20,thet1List)



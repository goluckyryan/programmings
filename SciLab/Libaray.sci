//right hand rotation matric around origin
//Latex $R\cdot \vec{v}$
// $R={cos(\theta),-sin(\theta)}$
//
//
clear
function u=Rotation2D(v,theta)
    u=[cos(theta),-sin(theta);sin(theta),cos(theta)]*v
endfunction

function R=Rotz(theta)
    R=[cos(theta),-sin(theta),0;sin(theta),cos(theta),0;0,0,1]    
endfunction

function R=Rotx(theta)
    R=[1,0,0;1,cos(theta),-sin(theta);0,sin(theta),cos(theta)]    
endfunction

function R=Roty(theta)
    R=[cos(theta),0,sin(theta);0,1,0;-sin(theta),0,cos(theta)]    
endfunction

function angle=polarangle(k)
    b=sqrt(k(1)^2+k(2)^2);
    theta=atan(b,k(3));
    phi=atan(k(2),k(1));
    angle={phi,theta}
endfunction

function angle=polarangle4D(k)
    b=sqrt(k(2)^2+k(3)^2);
    theta=atan(b,k(4));
    phi=atan(k(3),k(2));
    angle={phi,theta}
endfunction

function u=Rotation3D(v,k,rot)
    angle=polarangle(k)
    u=(Rotz(angle(1))*Roty(angle(2))*Rotz(rot)*Roty(-angle(2))*Rotz(-angle(1))*(v'))'
endfunction

function u=Rot4D(k,rot)
    angle=polarangle(k);
    utemp=Rotz(angle(1))*Roty(angle(2))*Rotz(rot)*Roty(-angle(2))*Rotz(-angle(1));
    u=eye(4,4);
    for i=2:4
        for j=2:4
            u(i,j)=utemp(i-1,j-1);
        end
    end
endfunction

function u=Rotation4D(v,k,rot)
    angle=polarangle(k);
    utemp=Rotz(angle(1))*Roty(angle(2))*Rotz(rot);
    u=eye(4,4);
    for i=2:4
        for j=2:4
            u(i,j)=utemp(i-1,j-1);
        end
    end
    u=(u*v')'
endfunction

function Lz=Lz4D(b)
    g=1/sqrt(1-b**2);
    Lz={g,0,0,g*b;
        0,1,0,0;
        0,0,1,0;
        g*b,0,0,g}
endfunction

function p=Pmomemtum4(m,T,theta,phi)
    momt=sqrt(2*m*T+T**2);
    p={m+T,momt*cos(phi)*sin(theta),momt*sin(phi)*sin(theta),momt*cos(theta)}
endfunction

function u=KE(p,m)
    u=p(1)-m
endfunction

function u=SphericalDist(id)
    if(id==3) then
        u={acos(2*rand()-1),2*%pi*(rand()-0.5)}
    elseif id==1 then
        u=acos(2*rand()-1)
    elseif id==2 then
        u=2*%pi*(rand()-0.5)
    end
endfunction

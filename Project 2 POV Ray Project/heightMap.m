n=10;
smooth_param = 0.4;
amplitude = 0.7;
last=2^n+1;
A=zeros(last,last);
%//disp(A)
A(1,1)=3;
A(1,last)=4;
A(last,1)=4;
A(last,last)=3;
for i=1:n
    h=last-1;
    d=(h/2^i);
  %  //printf("d=%i\n",d)
    for j=1:2^(i-1)
        for k=1:2^(i-1)
            A((j-1)*2*d+1,(k-1)*2*d+1+d)=1/2*(A((j-1)*2*d+1,(k-1)*2*d+1)+A((j-1)*2*d+1,k*2*d+1))+amplitude*(2*rand()-1)*2^(-smooth_param*n);
            A(j*2*d+1,(k-1)*2*d+1+d)=1/2*(A(j*2*d+1,(k-1)*2*d+1)+A(j*2*d+1,k*2*d+1))+amplitude*(2*rand()-1)*2^(-smooth_param*n);
            A((j-1)*2*d+1+d,(k-1)*2*d+1)=1/2*(A((j-1)*2*d+1,(k-1)*2*d+1)+A(j*2*d+1,(k-1)*2*d+1))+amplitude*(2*rand()-1)*2^(-smooth_param*n);
            A((j-1)*2*d+1+d,k*2*d+1)=1/2*(A((j-1)*2*d+1,k*2*d+1)+A(j*2*d+1,k*2*d+1))+amplitude*(2*rand()-1)*2^(-smooth_param*n);
            A((j-1)*2*d+1+d,(k-1)*2*d+1+d)=1/4*(A((j-1)*2*d+1,(k-1)*2*d+1+d)+A(j*2*d+1,(k-1)*2*d+1+d)+A((j-1)*2*d+1+d,(k-1)*2*d+1)+A((j-1)*2*d+1+d,k*2*d+1))+amplitude*(2*rand()-1)*2^(-smooth_param*n);
         %   //disp(A)
        %    //input("enter ")
        end
    end
  %  //disp(A)
 %   //input("enter ")
end
%//disp(A)
%plot3(1:last,1:last,A)

I= mat2gray(A);
figure;
imshow(I);

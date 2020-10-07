program jakobi_temp

implicit none
include 'mpif.h'
integer:: rank, np, err, ST(MPI_STATUS_SIZE)
INTEGER:: i, j, n, m, s, k, iter, top, bottom,p, it, r,d, c

real:: e, er,er1, dt1, dt2
double precision, allocatable:: tm(:,:), row(:), ar(:,:), t(:,:), disp(:), tb(:,:)


CALL MPI_INIT(err)
CALL MPI_COMM_RANK(MPI_COMM_WORLD, rank, err)
CALL MPI_COMM_SIZE(MPI_COMM_WORLD, np, err)

if (rank.eq.0) then
write(6,*) 'Input number of slices'
write(6,*) 'Input number of lines:'
read(*,*)n
write(6,*) 'Input number of columns:'
read(*,*)m
allocate(tm(n,m))
tm(:,:)=0.d0
write(6,*) 'Input temperatures on 4 corners'
write(6,*) 'Upper left:'
read(*,*) tm(1,1)
write(6,*) 'Upper right:'
read(*,*) tm(1,m)
write(6,*) 'Lower left:'
read(*,*) tm(n,1)
write(6,*) 'Lower right:'
read(*,*) tm(n,m)

write(6,*) 'Number of iterrations ='
read(*,*) iter

write(6,*) 'Accuracy ='
read(*,*) e
endif

CALL MPI_BCAST(n, 1, MPI_INTEGER, 0, MPI_COMM_WORLD, err)
CALL MPI_BCAST(m, 1, MPI_INTEGER, 0, MPI_COMM_WORLD, err)
CALL MPI_BCAST(e,1, MPI_REAL, 0, MPI_COMM_WORLD, err)
CALL MPI_BCAST(iter,1, MPI_INTEGER, 0, MPI_COMM_WORLD, err)

allocate(row(np))
if (rank.eq.0) then

dt1=(tm(1,m)-tm(1,1))/m
dt2=(tm(n,m)-tm(n,1))/m
do i=2, m-1
tm(1,i)=tm(1,1)+i*dt1
tm(n,i)=tm(n,1)+i*dt2
enddo

dt1=(tm(n,1)-tm(1,1))/n
dt2=(tm(n,m)-tm(1,m))/n
do i=2, n-1
tm(i,1)=tm(1,1)+i*dt1
tm(i,m)=tm(1,m)+i*dt2
enddo
write(6,*)'Your list is'
do i = 1, n
write(6,'(100f8.3)')(tm(i,j), j=1,m)
enddo

allocate(disp(np))
disp(:)=n/np

do i=1,mod(n,np)
disp(i)=disp(i)+1
enddo
row(:)=disp(:)+1

do i=2,np-1
row(i)=row(i)+1
enddo

write(6,*)'disp = ', disp

write(6,*)'row = ', row


s=disp(1)-2
do i = 1, np-1
c=row(i+1)
allocate(tb(c,m))
do j = 1, c
do k = 1, m
tb(j,k)=tm(j+s+i, k)
enddo
enddo
s = s + disp(i+1)-1
CALL MPI_SEND(tb,m*c, MPI_DOUBLE_PRECISION, i, i*10, MPI_COMM_WORLD, ERR)
write(6,*)'Band on ',i,'=='
do p=1,c
write(6,'(100f8.3)')(tb(p,r),r =1,m)
enddo
deallocate(tb)
enddo

endif


CALL MPI_BCAST(row, np, MPI_DOUBLE_PRECISION, 0, MPI_COMM_WORLD, err)
if (rank .eq. 0) then
c=row(1)
allocate(tb(c,m))
do i = 1, c
do j = 1, m
tb(i,j)=tm(i, j)
enddo
enddo
else
c = row(rank + 1)
allocate(tb(c,m), t(c,m))
CALL MPI_RECV(tb, c*m, MPI_DOUBLE_PRECISION, 0, rank*10, MPI_COMM_WORLD, ST, ERR)
endif



!определение номеров процессов снизу и сверху
if (rank.eq.0) then
top=MPI_PROC_NULL
else
top=rank-1
endif

if(rank.eq.np-1) then
bottom=MPI_PROC_NULL
else
bottom=rank+1
endif

!цикл поуказанным  итерациям
t=tb

do it=1, iter
er1=0
er=0

c=row(rank+1)
!рассчет
do i=2, c-1
do j=2, m-1
t(i,j)=(tb(i-1,j)+tb(i+1,j)+tb(i,j-1)+tb(i,j+1))/4
er=er+(t(i,j)-tb(i,j))**2
enddo
enddo

tb=t



CALL MPI_SENDRECV(t(2,:), m, MPI_DOUBLE_PRECISION, top, rank+(it*(it+100)+it), &
tb(c, :), m, MPI_DOUBLE_PRECISION, bottom,  (rank+1)+(it*(it+100)+it), &
MPI_COMM_WORLD, ST, err)
CALL MPI_SENDRECV(t(c-1,:), m, MPI_DOUBLE_PRECISION, bottom,  rank+(it*(it+999)+it), &
tb(1,:), m,MPI_DOUBLE_PRECISION,top,  (rank-1)+(it*(it+999)+it), &
MPI_COMM_WORLD, ST, err)

CALL MPI_ALLREDUCE(er, er1, 1, MPI_REAL, MPI_SUM, MPI_COMM_WORLD, err)
er1=sqrt(er1)


if (er1.lt.e) goto 777
enddo
777 continue

write(6,*)'Band on',rank,'==', tb

if (rank.eq.0) then
allocate(ar(n,m))
do i=1, c-1
do j=1, m
ar(i,j)=tb(i,j)
enddo
enddo
deallocate(tb)
else
CALL MPI_SEND(tb, c*m, MPI_DOUBLE_PRECISION, 0, RANK+1, MPI_COMM_WORLD, ERR)
endif


if(rank.eq.0) then
s = disp(1)
do p = 1, np-1
if(p.eq.np-1) then
r=0
else
r=1
endif
c = row(p+1)
allocate(tb(c,m))
CALL MPI_RECV(tb, c*m, MPI_DOUBLE_PRECISION, p,p+1, MPI_COMM_WORLD, ST, ERR)
do i = 2,c-r
do j = 1, m
ar(i+s-1, j)=tb(i, j)
enddo
enddo
s = s+disp(p+1)
deallocate(tb)
enddo





write(6,*)'error=', er1
write(6,*) 'RES:'
do i=1, n
write(6, '(100f8.3)')(ar(i,j), j=1,m)
enddo
endif
CALL MPI_FINALIZE(err)
end

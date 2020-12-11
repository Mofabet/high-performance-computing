subroutine factor(n, fact)

    implicit none
    integer, intent(in) :: n  
    integer, intent(out) :: fact
    integer :: i    
    
    fact = n 
    do i = 1, n-1
        fact = fact*i 
    end do
     
    end subroutine
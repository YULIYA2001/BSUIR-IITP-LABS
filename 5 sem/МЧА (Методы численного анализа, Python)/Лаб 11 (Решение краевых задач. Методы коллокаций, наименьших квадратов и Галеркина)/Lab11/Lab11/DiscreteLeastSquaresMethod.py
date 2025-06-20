import numpy as np
import sympy as sp 

from scipy.integrate import quad
from scipy import linalg


def discrete_LSM(P, Q, F, n, N, left, right, fi):

    X = np.zeros(N)
    for i in range(N):
        X[i] = left + ((i+1) - 0.5)/N * (right + 1)

    M = np.zeros((n, n))
    V = np.zeros(n)

    for i in range(n):

        x = sp.symbols('x')
        diff2_fi_i = sp.diff(fi(x, i+1), x, x)
        diff1_fi_i = sp.diff(fi(x, i+1), x)

        for j in range(n):            
            diff2_fi = sp.diff(fi(x, j+1), x, x)
            diff1_fi = sp.diff(fi(x, j+1), x)
            
            sum_M = 0            
            for k in range(N):
                try:
                    Q_ = Q.subs([(x, X[k])])
                except:
                    Q_ = Q
                try:
                    P_ = P.subs([(x, X[k])])
                except:
                    P_ = P
                sum_M += (diff2_fi.subs([(x, X[k])]) + diff1_fi.subs([(x, X[k])]) * P_ +\
                        fi(X[k], j+1) * Q_) * \
                        (diff2_fi_i.subs([(x, X[k])]) + diff1_fi_i.subs([(x, X[k])]) * P_ +\
                        fi(X[k], i+1) * Q_)
            M[i][j] = sum_M

        sum_V = 0
        for k in range(N):
            try:
                F_ = F.subs([(x, X[k])])
            except:
                F_ = F
            try:
                Q_ = Q.subs([(x, X[k])])
            except:
                Q_ = Q
            try:
                P_ = P.subs([(x, X[k])])
            except:
                P_ = P

            sum_V += F_ * (diff2_fi_i.subs([(x, X[k])]) + diff1_fi_i.subs([(x, X[k])]) * P_ +\
                    fi(X[k], i+1) * Q_)
        V[i] = sum_V   

    print("\nСЛАУ в матричном виде для нахождения коэфициентов a1, ..., an")
    for i in range(n):
        for j in range(n):
            print("{:.5f}".format(M[i][j]), end=' ')
        print("    |     {:.5f}".format(V[i]))

    A = list(linalg.solve(M, V)) 
    print("\nРешение системы: вектор A = {0}".format(A))

    return A























'''    ! -----------------------------------------------------------------------------------------------------------------
    ! Дискретный МНК
    ! -----------------------------------------------------------------------------------------------------------------
    subroutine disc_least_squares_method(x_min, x_max, n, solution, solution_ext, f, a, p, q, basic, &
            x_points, is_print, is_draw, info)

        implicit none

        real(dp), external :: f, p, q, basic, a
        character(*), intent(in) :: info
        integer, intent(in) :: n, x_points
        real(dp), intent(in) :: x_min, x_max
        logical, intent(in) :: is_print, is_draw

        real(dp), intent(out) :: solution(:), solution_ext(:)

        real(dp), dimension(1:x_points) :: x_list
        real(dp), dimension(1:n) :: free_members_vector
        real(dp), dimension(:), allocatable :: x_dist
        real(dp), dimension(:,:), allocatable :: help_matrix
        real(dp), dimension(1:n, 1:n) :: coef_matrix

        integer :: i, j, l, error, nn
        real(dp) :: temp, l2

        nn = 2 * n

        allocate(x_dist(1:nn), help_matrix(1:n, 1:nn))

        solution = 0._dp; x_list = 0._dp; solution_ext = 0._dp; free_members_vector = 0._dp;
        coef_matrix = 0._dp; help_matrix = 0._dp; x_dist = 0._dp

        ! точки распределения
        call noised_linspace(from=x_min, to=x_max, array=x_dist, noise=0._dp)

        do i = 1, n
            do j = 1, nn
                help_matrix(i, j) = a(x_dist(j)) * basic(x_dist(j), i-1, 2) + p(x_dist(j)) * basic(x_dist(j), i-1, 1) + &
                        q(x_dist(j)) * basic(x_dist(j), i-1, 0)
            end do
        end do

        ! иниициализация матрицы коэффициентов
        i = 1; j = 1; l = 1;
        do while(i <= n)
            j = 1
            do while(j <= i)
                l = 1
                do while(l <= nn)
                    coef_matrix(i, j) = coef_matrix(i, j) + help_matrix(j, l) * help_matrix(i, l)
                    l = l + 1
                end do
                j = j + 1
            end do
            i = i + 1
        end do

        do i = 1, n
            do j = 1, n
                coef_matrix(i, j) = coef_matrix(j, i)
            end do
        end do

        ! инициализация вектора свободных членов
        do i = 1, n
            temp = 0
            do j = 1, nn
                temp = temp + f(x_dist(j)) * (a(x_dist(j)) * basic(x_dist(j), i-1, 2) + p(x_dist(j)) * basic(x_dist(j), i-1, 1) + &
                        q(x_dist(j)) * basic(x_dist(j), i-1, 0))
            end do
            free_members_vector(i) = temp
        end do

        ! решение системы линейных уравнений
        call lu_solve(coef_matrix, free_members_vector, solution, error)
        if (error > 0) then
            call qr_solve(n, n, coef_matrix, free_members_vector, solution)
        end if

        ! численное решение
        call noised_linspace(x_min, x_max, x_list, noise=0._dp)
        do i = 1, x_points
            solution_ext(i) = solution_ext(i) + basic(x_list(i), 0, 0)
            do j = 2, size(solution)
                solution_ext(i) = solution_ext(i) + solution(j) * basic(x_list(i), j-1, 0)
            end do
        end do

        ! вычисление погрешности
        l2 = l2_norm(residual2, x_min, x_max, n, solution, f, a, p, q, basic, 100)

        if (is_print) then

            print *, ''
            print *, info

            print "(/, a19)", "Distribution points:"
            print *, (x_dist(i), i = 1, nn)

            print "(/, a19)", "Coefficient matrix:"
            do i = 1, n
                print *, (coef_matrix(i, j), j = 1, n)
            end do

            print "(/, a20)", "Free members vector:"
            print *, (free_members_vector(i), i = 1, n)

            if (error > 0) then
                print "(/, a42)", "LU_SOLVE: Matrix is special. Use QR_SOLVE."
            end if

            print "(/, a23)", "Linear system solution:"
            print *, (solution(i), i = 1, n)

            print "(/, a21)", "Collocation solution:"
            print *, (solution_ext(i), i = 1, x_points)

            print "(/, a8)", "L2 norm:"
            print *, l2

        end if

        if (is_draw) then
            call gp%title(info)
            call gp%xlabel('X')
            call gp%ylabel('Yn(x) = φ0(x) + a1 * φ1(x) + ... + an * φn(x)')
            call gp%plot(x_list, solution_ext, 'with lines')
        end if

        deallocate(x_dist, help_matrix)

    end subroutine disc_least_squares_method
'''


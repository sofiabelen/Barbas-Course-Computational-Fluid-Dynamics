#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>

void print_vec(const std::vector<std::vector<double> > &vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            printf("%.4llf ", vec[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void calculate_b(int prev_i, int next_i, int cur_i, int j,
        const double &dx, const double &dy,
        const double &dt, const double &rho,
        std::vector<std::vector<double> > &un,
        std::vector<std::vector<double> > &vn,
        std::vector<std::vector<double> > &b) {
    double term1 = 1.0 / dt * ((un[next_i][j] - un[prev_i][j])
            / (2.0 * dx) +     (vn[cur_i][j + 1] - vn[cur_i][j - 1])
            / (2.0 * dy));
    
    double term2 = pow((un[next_i][j] - un[prev_i][j])
            / (2.0 * dx), 2.0); 
    
    double term3 = ((un[cur_i][j + 1] - un[cur_i][j - 1]) / (2.0 * dy)) *
                   ((vn[next_i][j] - vn[prev_i][j]) / (2.0 * dx));
    
    double term4 = pow((vn[cur_i][j + 1] - vn[cur_i][j - 1])
            / (2.0 * dy), 2.0);
    
    b[cur_i][j] = rho * (term1 - term2 - 2.0 * term3 - term4);
}

void calculate_p(int prev_i, int next_i, int cur_i, int j,
        const double &dx, const double &dy,
        std::vector<std::vector<double> > &un,
        std::vector<std::vector<double> > &vn,
        std::vector<std::vector<double> > &P,
        std::vector<std::vector<double> > &Pn,
        std::vector<std::vector<double> > &b) {
    P[cur_i][j] = (((Pn[next_i][j] + Pn[prev_i][j]) * dy * dy +
                (Pn[cur_i][j + 1] + Pn[cur_i][j - 1]) * dx * dx)
        / (2.0 * (dx * dx + dy * dy))
        - dx * dx * dy * dy
        / (2.0 * (dx * dx + dy * dy)) * b[cur_i][j]);
}

void calculate_u(int prev_i, int next_i, int cur_i, int j,
        const double &dx, const double &dy, const double &dt,
        const double &rho, const double &nu, const double &F,
        std::vector<std::vector<double> > &un,
        std::vector<std::vector<double> > &vn,
        std::vector<std::vector<double> > &u,
        std::vector<std::vector<double> > &P) {
    double term1 = un[cur_i][j] * dt / dx *
        (un[cur_i][j] - un[prev_i][j]);
    
    double term2 = vn[cur_i][j] * dt / dy *
        (un[cur_i][j] - un[cur_i][j - 1]);
    
    double term3 = dt / (2.0 * rho * dx) *
        (P[next_i][j] - P[prev_i][j]);
    
    double term4 = nu * (dt / (dx * dx) *
        (un[next_i][j] - 2.0 * un[cur_i][j] + un[prev_i][j]) +
        dt / (dy * dy) *
        ( un[cur_i][j + 1] - 2.0 * un[cur_i][j] + un[cur_i][j - 1]));
    
    u[cur_i][j] = un[cur_i][j] - term1  - term2 - term3 + term4 +
        dt * F;
}

void calculate_v(int prev_i, int next_i, int cur_i, int j,
        const double &dx, const double &dy, const double &dt,
        const double &rho, const double &nu,
        std::vector<std::vector<double> > &un,
        std::vector<std::vector<double> > &vn,
        std::vector<std::vector<double> > &v,
        std::vector<std::vector<double> > &P) {
    double term1 = un[cur_i][j] * dt / dx *
        (vn[cur_i][j] - vn[prev_i][j]);
    
    double term2 = vn[cur_i][j] * dt / dy *
        (vn[cur_i][j] - vn[cur_i][j - 1]);
    
    double term3 = dt / (2.0 * rho * dy) *
        (P[cur_i][j + 1] - P[cur_i][j - 1]);
    
    double term4 = nu * (dt / (dx * dx) *
        (vn[next_i][j] - 2.0 * vn[cur_i][j] + vn[prev_i][j]) +
        dt / (dy * dy) *
        (vn[cur_i][j + 1] - 2.0 * vn[cur_i][j] + vn[cur_i][j - 1]));
    
    v[cur_i][j] = vn[cur_i][j] - term1 - term2 - term3 + term4;
}

int main() {
    std::ofstream output_u("Data/u12"), output_v("Data/v12"),
        counter_out, output_p("Data/p12");
    std::ifstream input("Parameters/input12"), counter_in;
    std::fstream log;

    int exp_count;
    counter_in.open("Parameters/counter");
    counter_in >> exp_count;
    counter_in.close();

    int nx, ny, nt, nat;
    double dx, dy, rho, nu, dt, real_time, F, mindiff, stepcount, udiff;

    input >> dx >> dt >> nat >> rho >> nu >> F >> mindiff;

    dy = dx;
    nx = static_cast<int>(2.0 / dx);
    ny = static_cast<int>(2.0 / dy);

    std::vector<std::vector<double> > b(nx,
            std::vector<double>(ny, 0.0));

    std::vector<std::vector<double> > u(nx,
            std::vector<double>(ny, 0.0));
    
    std::vector<std::vector<double> > v(nx,
            std::vector<double>(ny, 0.0));

    std::vector<std::vector<double> > P(nx,
            std::vector<double>(ny, 0.0));

    stepcount = 0;
    udiff = mindiff + 1.0;

    while(udiff > mindiff) {
        std::vector<std::vector<double> > un, vn;

        un = u;
        vn = v;

        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                calculate_b(i - 1, i + 1, i, j, dx, dy, dt,
                        rho, un, vn, b);
            }
        }
        
        // periodic boundary conditions at x = 0, 2
        for (int j = 1; j < ny - 1; j++) {
            calculate_b(nx - 1, 1, 0, j, dx, dy, dt,
                    rho, un, vn, b);

            calculate_b(nx - 2, 0, nx - 1, j, dx, dy, dt,
                    rho, un, vn, b);
        }

        // Poisson equation
        for (int at = 0; at < nat; at++) {
            std::vector<std::vector<double> > Pn = P;

            for (int i = 1; i < nx - 1; i++) {
                for (int j = 1; j < ny - 1; j++) {
                    calculate_p(i - 1, i + 1, i, j, dx, dy,
                            un, vn, P, Pn, b);
                }
            }

            // periodic boundary conditions at x = 0, 2
            for (int j = 0; j < ny; j++) {
                calculate_p(nx - 1, 1, 0, j, dx, dy,
                        un, vn, P, Pn, b);

                calculate_p(nx - 2, 0, nx - 1, j, dx, dy,
                        un, vn, P, Pn, b);
            }

            // boundary condition: dp/dy = 0 at y = 0, 2
            for (int i = 0; i < nx; i++) {
                P[i][0] = P[i][1];
                P[i][ny - 1] = P[i][ny - 2];
            }
        }

        // Navier-Stokes
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                calculate_u(i - 1, i + 1, i, j, dx, dy, dt,
                        rho, nu, F, un, vn, u, P);

                calculate_v(i - 1, i + 1, i, j, dx, dy, dt,
                        rho, nu, un, vn, v, P);
            }
        }
        // periodic boundary conditions at x = 0, 2
        for (int j = 1; j < ny - 1; j++) {
            calculate_u(nx - 1, 1, 0, j, dx, dy, dt,
                    rho, nu, F, un, vn, u, P);

            calculate_u(nx - 2, 0, nx - 1, j, dx, dy, dt,
                    rho, nu, F, un, vn, u, P);

            calculate_v(nx - 1, 1, 0, j, dx, dy, dt,
                    rho, nu, un, vn, v, P);

            calculate_v(nx - 2, 0, nx - 1, j, dx, dy, dt,
                    rho, nu, un, vn, v, P);
        }

        double sum_u = 0, sum_un = 0;
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                sum_u += u[i][j];
                sum_un += un[i][j];
            }
        }
        udiff = (sum_u - sum_un) / sum_u;

        stepcount++;
    }

    real_time = static_cast<double>(stepcount) * dt;

    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            output_u << u[i][j] << " ";
            output_v << v[i][j] << " ";
            output_p << P[i][j] << " ";
        }
        output_u << "\n";
        output_v << "\n";
        output_p << "\n";
    }

    counter_out.open("Parameters/counter");
    counter_out << exp_count + 1;
    counter_out.close();

    log.open("Data/log", std::ios_base::app);
    log << "Experiment #" << exp_count << " Step 12\n";
    log << "dx: " << dx << "\n";
    log << "time: " << real_time << "\n";
    log << "nx: " << nx << "\n";
    log << "ny: " << ny << "\n";
    log << "nu: " << nu << "\n";
    log << "rho: " << rho << "\n";
    log << "F: " << F << "\n";
    log << "mindiff: " << mindiff << "\n";
    log << "stepcount: " << stepcount << "\n\n";

    return 0;
}

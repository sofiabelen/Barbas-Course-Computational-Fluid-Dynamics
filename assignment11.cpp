#include <cstdio>
#include <vector>
#include <fstream>
#include <cmath>

void print_vec(const std::vector<std::vector<long double> > &vec) {
    for (int i = 0; i < vec.size(); i++) {
        for (int j = 0; j < vec[i].size(); j++) {
            printf("%.4llf ", vec[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

int main() {
    std::ofstream output_u("Data/u11"), output_v("Data/v11"),
        counter_out, output_p("Data/p11");
    std::ifstream input("Parameters/input11"), counter_in;
    std::fstream log;

    int exp_count;
    counter_in.open("Parameters/counter");
    counter_in >> exp_count;
    counter_in.close();

    int nx, ny, nt, nat;
    long double dx, dy, rho, nu, dt, real_time;

    input >> dx >> dt >> real_time >> nat >> rho >> nu;

    dy = dx;
    nx = static_cast<int>(2.0 / dx);
    ny = static_cast<int>(2.0 / dy);
    nt = static_cast<int>(real_time / dt);

    std::vector<std::vector<long double> > b(nx,
            std::vector<long double>(ny, 0.0));

    std::vector<std::vector<long double> > u(nx,
            std::vector<long double>(ny, 0.0));
    
    std::vector<std::vector<long double> > v(nx,
            std::vector<long double>(ny, 0.0));

    std::vector<std::vector<long double> > P(nx,
            std::vector<long double>(ny, 0.0));

    for (int t = 0; t < nt; t++) {
        std::vector<std::vector<long double> > un, vn;

        un = u;
        vn = v;

        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                long double term1 = 1.0 / dt * ((un[i + 1][j] - un[i - 1][j])
                        / (2.0 * dx) +     (vn[i][j + 1] - vn[i][j - 1])
                        / (2.0 * dy));

                long double term2 = pow((un[i + 1][j] - un[i - 1][j])
                        / (2.0 * dx), 2.0); 

                long double term3 = ((un[i][j + 1] - un[i][j - 1]) / (2.0 * dy)) *
                               ((vn[i + 1][j] - vn[i - 1][j]) / (2.0 * dx));

                long double term4 = pow((vn[i][j + 1] - vn[i][j - 1])
                        / (2.0 * dy), 2.0);

                b[i][j] = rho * (term1 - term2 - 2.0 * term3 - term4);
            }
        }

        // Poisson equation
        for (int at = 0; at < nat; at++) {
            // std::vector<std::vector<long double> > Pn(nx,
            //         std::vector<long double>(ny));

            std::vector<std::vector<long double> > Pn = P;

            for (int i = 1; i < nx - 1; i++) {
                for (int j = 1; j < ny - 1; j++) {
                    P[i][j] = (((Pn[i + 1][j] + Pn[i - 1][j]) * dy * dy +
                                (Pn[i][j + 1] + Pn[i][j - 1]) * dx * dx)
                        / (2.0 * (dx * dx + dy * dy))
                        - dx * dx * dy * dy
                        / (2.0 * (dx * dx + dy * dy)) * b[i][j]);
                }
            }

            for (int i = 0; i < nx; i++) {
                // boundary condition: dp/dy = 0 at y = 0
                P[i][0] = P[i][1];

                // boundary condition: p = 0 at y = 2
                P[i][ny - 1] = 0;
            }

            // boundary condition: dp/dx = 0 at x = 0, 2
            for (int j = 0; j < ny; j++) {
                P[0][j] = P[1][j];
                P[nx - 1][j] = P[ny - 2][j];
            }
        }

        // Navier-Stokes
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                long double term1 = un[i][j] * dt / dx *
                    (un[i][j] - un[i - 1][j]);

                long double term2 = vn[i][j] * dt / dy *
                    (un[i][j] - un[i][j - 1]);

                long double term3 = dt / (2.0 * rho * dx) *
                    (P[i + 1][j] - P[i - 1][j]);

                long double term4 = nu * (dt / (dx * dx) *
                    (un[i + 1][j] - 2.0 * un[i][j] + un[i - 1][j]) +
                    dt / (dy * dy) *
                    ( un[i][j + 1] - 2.0 * un[i][j] + un[i][j - 1]));

                u[i][j] = un[i][j] - term1  - term2 - term3 + term4;

                term1 = un[i][j] * dt / dx *
                    (vn[i][j] - vn[i - 1][j]);

                term2 = vn[i][j] * dt / dy *
                    (vn[i][j] - vn[i][j - 1]);

                term3 = dt / (2.0 * rho * dy) *
                    (P[i][j + 1] - P[i][j - 1]);

                term4 = nu * (dt / (dx * dx) *
                    (vn[i + 1][j] - 2.0 * vn[i][j] + vn[i - 1][j]) +
                    dt / (dy * dy) *
                    (vn[i][j + 1] - 2.0 * vn[i][j] + vn[i][j - 1]));

                v[i][j] = vn[i][j] - term1 - term2 - term3 + term4;
            }
        }

        // boundary condition: u = 1 at y = 2
        for (int i = 0; i < nx; i++) {
            u[i][ny - 1] = 1.0;
        }
    }

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
    log << "Experiment #" << exp_count << " Step 11\n";
    log << "dx: " << dx << "\n";
    log << "time: " << real_time << "\n";
    log << "nt: " << nt << "\n";
    log << "nx: " << nx << "\n";
    log << "ny: " << ny << "\n";
    log << "nu: " << nu << "\n";
    log << "rho: " << rho << "\n\n";

    return 0;
}

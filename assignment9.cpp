#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ofstream output("Data/output9"), counter_out;
    std::ifstream input("Parameters/input9"), counter_in;
    std::fstream log;

    int exp_count;
    counter_in.open("Parameters/counter");
    counter_in >> exp_count;
    counter_in.close();

    int nx, ny, nt;
    double dx, dy;

    input >> dx >> nt;

    dy = dx;
    nx = static_cast<int>(2.0 / dx);
    ny = static_cast<int>(1.0 / dy);

    std::vector<std::vector<std::vector<double> > > P(nx,
            std::vector<std::vector<double> >(ny,
            std::vector<double>(nt, 0.0)));

    // Boundary condition p = y at x = 2, p = 0 at x = 0
    for (int j = 0; j < ny; j++) {
        double yj = static_cast<double>(j) * dy;
        for (int t = 0; t < nt; t++) {
            P[nx - 1][j][t] = yj;
        }
    }

    // Boundary condition dP/dy = 0 at y = 0, 1
    for (int i = 0; i < nx; i++) {
        P[i][ny - 1][0] = P[i][ny - 2][0];
        P[i][0][0] = P[i][1][0];
    }

    for (int t = 0; t < nt - 1; t++) {
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                P[i][j][t + 1] = (dy * dy * (P[i + 1][j][t] +
                    P[i - 1][j][t]) + dx * dx * (P[i][j + 1][t]
                    + P[i][j - 1][t])) / (2.0 * (dx * dx + dy * dy));
            }

            // Boundary condition dP/dy = 0 at y = 0, 1
            P[i][ny - 1][t + 1] = P[i][ny - 2][t + 1];
            P[i][0][t + 1] = P[i][1][t + 1];
        }
    }

    for (int t = 0; t < nt; t++) {
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < ny; j++) {
                output << P[i][j][t] << " ";
            }
            output << "\n";
        }
        output << "\n";
    }

    counter_out.open("Parameters/counter");
    counter_out << exp_count + 1;
    counter_out.close();

    log.open("Data/log", std::ios_base::app);
    log << "Experiment #" << exp_count << " Step 9\n";
    log << "dx: " << dx << "\n";
    log << "nt: " << nt << "\n";
    log << "nx: " << nx << "\n";
    log << "ny: " << ny << "\n\n";

    return 0;
}

#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ofstream output("Data/output5");
    std::ifstream input("Parameters/input5");

    int nx, nt;
    double dt, c;

    input >> nx >> nt >> dt >> c;

    double dx = 2.0 / static_cast<double>(nx);

    std::vector<std::vector<std::vector<double> > > u(nx,
            std::vector<std::vector<double> >(nx,
            std::vector<double>(nt, 1)));

    for (int i = 0; i < nx; i++) {
        double xi = static_cast<double>(i) * dx;
        for (int j = 0; j < nx; j++) {
            double yj = static_cast<double>(j) * dx;

            if (0.5 <= xi && xi <= 1.0 &&
                    0.5 <= yj && yj <= 1.0) {
                u[i][j][0] = 2.0;
            } else {
                u[i][j][0] = 1.0;
            }
        }
    }

    for (int t = 0; t < nt - 1; t++) {
        for (int i = 1; i < nx; i++) {
            for (int j = 1; j < nx; j++) {
                u[i][j][t + 1] = u[i][j][t] - c * dt / dx *
                    (u[i][j][t] - u[i - 1][j][t]) - c * dt / dx *
                    (u[i][j][t] - u[i][j - 1][t]);
            }
        }
    }

    for (int t = 0; t < nt; t++) {
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < nx; j++) {
                output << u[i][j][t] << " ";
            }
            output << "\n";
        }
        output << "\n";
    }

    return 0;
}

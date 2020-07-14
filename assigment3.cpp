#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ofstream output("Data/output3");
    std::ifstream input("Parameters/input3");

    int nx, nt;
    double dt, nu;

    input >> nx >> nt >> dt >> nu;

    double dx = 2.0 / static_cast<double>(nx);

    std::vector<std::vector<double> > u(nx,
            std::vector<double>(nt));

    for (int i = 0; i < nx; i++) {
        double xi = static_cast<double>(i) * dx;

        if (0.5 <= xi && xi <= 1.0) {
            u[i][0] = 2.0;
        } else {
            u[i][0] = 1.0;
        }
    }

    for (int t = 0; t < nt - 1; t++) {
        for (int i = 1; i < nx - 1; i++) {
            u[i][t + 1] = u[i][t] + nu * dt / (dx * dx) * (u[i + 1][t]
                    - 2 * u[i][t] + u[i - 1][t]);
        }

        u[0][t + 1] = u[0][t] + nu * dt / (dx * dx) * (u[1][t]
                - 2 * u[0][t] + u[nx - 2][t]);
        u[nx - 1][t + 1] = u[0][t + 1];
    }

    for (int t = 0; t < nt; t++) {
        for (int i = 0; i < nx; i++) {
            output << u[i][t] << " ";
        }
        output << "\n";
    }

    return 0;
}

#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ofstream output("Data/output2");
    std::ifstream input("Parameters/input2");

    int nx, nt;
    double dt;

    input >> nx >> nt >> dt;

    double dx = 2.0 / static_cast<double>(nx);

    std::vector<std::vector<double> > u(nx,
            std::vector<double>(nt));

    for (int i = 1; i < nx - 1; i++) {
        double xi = static_cast<double>(i) * dx;

        if (0.5 <= xi && xi <= 1.0) {
            u[i][0] = 2.0;
        } else {
            u[i][0] = 1.0;
        }
    }

    for (int t = 0; t < nt - 1; t++) {
        for (int i = 1; i < nx; i++) {
            u[i][t + 1] = u[i][t] - u[i][t] * dt / dx
                * (u[i][t] - u[i - 1][t]);
        }
    }

    for (int t = 0; t < nt; t++) {
        for (int i = 0; i < nx; i++) {
            output << u[i][t] << " ";
        }
        output << "\n";
    }

    return 0;
}

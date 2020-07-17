#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ofstream output1("Data/output6_1"), output2("Data/output6_2");
    std::ifstream input("Parameters/input6");

    int nx, nt;
    double dt;

    input >> nx >> nt >> dt;

    double dx = 2.0 / static_cast<double>(nx);

    std::vector<std::vector<std::vector<double> > > u(nx,
            std::vector<std::vector<double> >(nx,
            std::vector<double>(nt, 1.0)));

    std::vector<std::vector<std::vector<double> > > v(nx,
            std::vector<std::vector<double> >(nx,
            std::vector<double>(nt, 1.0)));

    for (int i = 0; i < nx; i++) {
        double xi = static_cast<double>(i) * dx;
        for (int j = 0; j < nx; j++) {
            double yj = static_cast<double>(j) * dx;

            if (0.5 <= xi && xi <= 1.0 && 0.5 <= yj && yj <= 1.0) {
                u[i][j][0] = 2.0;
                v[i][j][0] = 2.0;
            } else {
                u[i][j][0] = 1.0;
                u[i][j][0] = 1.0;
            }
        }
    }

    for (int t = 0; t < nt - 1; t++) {
        for (int i = 1; i < nx; i++) {
            for (int j = 1; j < nx; j++) {
                u[i][j][t + 1] = u[i][j][t] - u[i][j][t] * (dt / dx) *
                    (u[i][j][t] - u[i - 1][j][t]) - v[i][j][t] * (dt /
                    dx) * (u[i][j][t] - u[i][j - 1][t]);

                v[i][j][t + 1] = v[i][j][t] - u[i][j][t] * (dt / dx) *
                    (v[i][j][t] - v[i - 1][j][t]) - v[i][j][t] * (dt /
                    dx) * (v[i][j][t] - v[i][j - 1][t]);
            }
        }
    }

    for (int t = 0; t < nt; t++) {
        for (int i = 0; i < nx; i++) {
            for (int j = 0; j < nx; j++) {
                output1 << u[i][j][t] << " ";
                output2 << v[i][j][t] << " ";
            }
            output1 << "\n";
            output2 << "\n";
        }
        output1 << "\n";
        output2 << "\n";
    }

    return 0;
}

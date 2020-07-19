#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ofstream output("Data/output10"), counter_out;
    std::ifstream input("Parameters/input10"), counter_in;
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
    
    std::vector<std::vector<std::vector<double> > > b(nx,
            std::vector<std::vector<double> >(ny,
            std::vector<double>(nt, 0.0)));

    for (int t = 0; t < nt; t++) {
        b[static_cast<int>(nx / 4.0)][static_cast<int>(ny / 4.0)][t] = 100.0;
        b[static_cast<int>(3.0 / 4.0 * nx)]
            [static_cast<int>(3.0 / 4.0 * ny)][t] = -100.0;
    }

    for (int t = 0; t < nt - 1; t++) {
        for (int i = 1; i < nx - 1; i++) {
            for (int j = 1; j < ny - 1; j++) {
                P[i][j][t + 1] = (dy * dy * (P[i + 1][j][t] +
                    P[i - 1][j][t]) + dx * dx * (P[i][j + 1][t]
                    + P[i][j - 1][t]) - b[i][j][t] * dx * dx * dy * dy)
                    / (2.0 * (dx * dx + dy * dy));
            }
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
    log << "Experiment #" << exp_count << " Step 10\n";
    log << "dx: " << dx << "\n";
    log << "nt: " << nt << "\n";
    log << "nx: " << nx << "\n";
    log << "ny: " << ny << "\n\n";

    return 0;
}

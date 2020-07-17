#include <cstdio>
#include <vector>
#include <fstream>

int main(int argc, char** argv) {
    std::ofstream output("Data/output1"), counter_out;
    std::ifstream input("Parameters/input1"), counter_in;
    std::fstream log;

    int exp_count;
    counter_in.open("Parameters/counter");
    counter_in >> exp_count;
    counter_in.close();

    counter_out.open("Parameters/counter");
    counter_out << exp_count + 1;
    counter_out.close();

    int nx, nt;
    double dt, dx, c, sigma, real_time;

    input >> dx >> real_time >> c >> sigma;

    dt = dx * sigma / c;
    nx = static_cast<int>(2.0 / dx);
    nt = static_cast<int>(real_time / dt);

    log.open("Data/log", std::ios_base::app);
    log << "Experiment #" << exp_count << " Step 1\n";
    log << "dt: " << dt << "\n";
    log << "dx: " << dx << "\n";
    log << "nx: " << nx << "\n";
    log << "time: " << real_time << "\n";
    log << "c: " << c << "\n";
    log << "sigma: " << sigma << "\n\n";

    std::vector<std::vector<double> > u(nx,
            std::vector<double>(nt, 1.0));

    for (int i = 0; i < nx; i++) {
        double xi = static_cast<double>(i) * dx;

        if (0.5 <= xi && xi <= 1.0) {
            u[i][0] = 2.0;
        } else {
            u[i][0] = 1.0;
        }
    }

    for (int t = 0; t < nt - 1; t++) {
        for (int i = 1; i < nx; i++) {
            u[i][t + 1] = u[i][t] - c * dt / dx
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

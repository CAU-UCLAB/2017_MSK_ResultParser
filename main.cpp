#include <fstream>
#include <iostream>
#include <string>
#include <vector>


int main(void) {
	//secondparser
	const std::string head("resultLambda");
	const std::string foot(".txt");

	std::string resB;
	std::string resR;
	std::string resALL;
	for (double lambda = 0.0; lambda <= 1.0; lambda += 0.1) {
		std::string name(head);
		name += std::to_string(lambda);
		name += "_";

		for (int i = 0; i < 60; i++) {
			std::string middle(name);

			middle += std::to_string(i);

			double B = 0;
			double R = 0;
			double sumEOn = 0;
			double RMax = 0;

			std::string finalname(middle);
			finalname += foot;

			std::cout << finalname << std::endl;

			std::ifstream file(finalname);
			if (!file.is_open()) {
				resB += ", ";
				resR += ", ";
				resALL += ", ";
				continue;
			}

			std::string line;
			while (!file.eof()) {
				std::getline(file, line);
				if (line.find("SUM of B : ") != std::string::npos) {
					B += std::stod(line.substr(11));
				}

				if (line.find("SUM of R : ") != std::string::npos) {
					R += std::stod(line.substr(11));
				}

				if (line.find("sum of EOn") != std::string::npos) {
					sumEOn = std::stod(line.substr(10));
				}

				if (line.find("RMax") != std::string::npos) {
					RMax = std::stod(line.substr(4));
				}

			}

			double Multiplier = RMax / ((5.0 / 9.0) * sumEOn * sumEOn);

			resB += std::to_string(B) + ", ";
			resR += std::to_string(R) + ", ";
			resALL += std::to_string(lambda * Multiplier * B + (1 - lambda) * R) + ", ";

			file.close();
		}

		resB += "\n";
		resR += "\n";
		resALL += "\n";
	}

	std::ofstream ofB("outB.csv");
	ofB << resB;
	ofB.close();

	std::ofstream ofR("outR.csv");
	ofR << resR;
	ofR.close();

	std::ofstream ofALL("outALL.csv");
	ofALL << resALL;
	ofALL.close();

	return 0;
}

int thirdParser(void) {
	//thirdparser
	const std::string head("resultLambda");
	const std::string foot(".txt");

	std::string resB;
	std::string resR;
	std::string resALL;
	for (double lambda = 0.0; lambda <= 1.0; lambda+= 0.1) {
		std::string name(head);
		name += std::to_string(lambda);
		name += "_";

		for (int i = 0; i < 60; i++) {
			std::string middle(name);

			middle += std::to_string(i);
			middle += "_";

			double B = 0;
			double R = 0;
			double Multiplier = 0;

			for (int j = 0; j < 5; j++) {
				std::string finalname(middle);

				finalname += std::to_string(j);
				finalname += foot;

				std::cout << finalname << std::endl;

				std::ifstream file(finalname);

				std::string line;
				while (!file.eof()) {
					std::getline(file, line);
					if (j == 4) {
						if (line.find("SUM of B : ") != std::string::npos) {
							B += std::stod(line.substr(11));
						}

						if (line.find("Multiplier ") != std::string::npos) {
							Multiplier = std::stod(line.substr(11));
						}
					}

					if (line.find("SUM of R : ") != std::string::npos) {
						R += std::stod(line.substr(11));
					}


				}


				file.close();
			}

			resB += std::to_string(B) + ", ";
			resR += std::to_string(R) + ", ";
			resALL += std::to_string(lambda * Multiplier * B + (1 - lambda) * R) + ", ";
		}

		resB += "\n";
		resR += "\n";
		resALL += "\n";
	}

	std::ofstream ofB("outB.csv");
	ofB << resB;
	ofB.close();

	std::ofstream ofR("outR.csv");
	ofR << resR;
	ofR.close();

	std::ofstream ofALL("outALL.csv");
	ofALL << resALL;
	ofALL.close();

	return 0;
}
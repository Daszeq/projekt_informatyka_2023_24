struct Result
{
    std::string text;
    int scor;

    bool operator<(const Result& other) const
    {
        return scor > other.scor;
    }
};

void saveResults(const std::vector<Result>& results)
{
    std::ofstream file("output.txt");
    if (file.is_open())
    {
        for (const auto& result : results)
        {
            file << result.text << " " << result.scor << std::endl;
        }
        file.close();
    }
    else
    {
        std::cerr << "Nie uda³o siê otworzyæ pliku do zapisu." << std::endl;
    }
}

std::vector<Result> loadResults()
{
    std::vector<Result> results;

    std::ifstream file("output.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            Result result;
            std::istringstream iss(line);
            iss >> result.text >> result.scor;
            results.push_back(result);
        }
        file.close();
    }

    return results;
}
std::string displayResults(const std::vector<Result>& results)
{
    std::string displayText;
    int i = 1;
    displayText += "Najlepsi Gracze:\n";
    for (const auto& result : results)
    {
        displayText += std::to_string(i) + ". Gracz: " + result.text + ",\tWynik: " + std::to_string(result.scor) + "pkt." + "\n";
        i++;
    }
    return displayText;
}
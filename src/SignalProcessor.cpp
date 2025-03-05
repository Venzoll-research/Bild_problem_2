#include "../include/SignalProcessor.h"

// Конструктор
SignalProcessor::SignalProcessor() {}

// Деструктор
SignalProcessor::~SignalProcessor() {}

// Копирующий конструктор
SignalProcessor::SignalProcessor(const SignalProcessor& other) {
    for (const auto& pair : other.filters) {
        filters[pair.first] = std::unique_ptr<FilterBase>(pair.second->clone());
    }
    for (const auto& pair : other.summators) {
        summators[pair.first] = std::unique_ptr<Summator>(pair.second->clone());
    }
    inputSignals = other.inputSignals;
    connections = other.connections;
}

// Оператор присваивания
SignalProcessor& SignalProcessor::operator=(const SignalProcessor& other) {
    if (this != &other) {
        filters.clear();
        summators.clear();
        inputSignals.clear();
        connections.clear();

        for (const auto& pair : other.filters) {
            filters[pair.first] = std::unique_ptr<FilterBase>(pair.second->clone());
        }
        for (const auto& pair : other.summators) {
            summators[pair.first] = std::unique_ptr<Summator>(pair.second->clone());
        }
        inputSignals = other.inputSignals;
        connections = other.connections;
    }
    return *this;
}

// Перемещающий конструктор
SignalProcessor::SignalProcessor(SignalProcessor&& other) noexcept
    : filters(std::move(other.filters)),
      summators(std::move(other.summators)),
      inputSignals(std::move(other.inputSignals)),
      connections(std::move(other.connections)) {}

// Перемещающий оператор присваивания
SignalProcessor& SignalProcessor::operator=(SignalProcessor&& other) noexcept {
    if (this != &other) {
        filters = std::move(other.filters);
        summators = std::move(other.summators);
        inputSignals = std::move(other.inputSignals);
        connections = std::move(other.connections);
    }
    return *this;
}

// Метод для добавления фильтра
void SignalProcessor::addFilter(const std::string& name, std::unique_ptr<FilterBase> filter) {
    filters[name] = std::move(filter);
}

// Метод для добавления сумматора
void SignalProcessor::addSummator(const std::string& name, std::unique_ptr<Summator> summator) {
    summators[name] = std::move(summator);
}

// Метод для установки входного сигнала
void SignalProcessor::setInputSignal(const std::string& inputName, const Signal& inputSignal) {
    inputSignals[inputName] = inputSignal;
}

// Метод для добавления связи между блоками
void SignalProcessor::addConnection(const std::string& outputName, const std::string& inputName) {
    connections[outputName].push_back(inputName);
}

// Метод для расчета выходов всех фильтров для данного входного сигнала
std::map<std::string, Signal> SignalProcessor::processSignal() {
    std::map<std::string, Signal> outputs;

    // Сначала обрабатываем все фильтры
    for (const auto& pair : filters) {
        const std::string& name = pair.first;
        FilterBase* filter = pair.second.get();
        if (inputSignals.find(name) != inputSignals.end()) {
            outputs[name] = filter->Filter(inputSignals[name]);
        }
    }

    // Затем обрабатываем все сумматоры
    for (const auto& pair : summators) {
        const std::string& name = pair.first;
        Summator* summator = pair.second.get();

        // Получаем входные значения для сумматора
        const auto& inputNames = connections[name];
        if (inputNames.size() != 2) {
            throw std::runtime_error("Summator must have exactly two inputs");
        }

        const Signal& inputSignal1 = outputs[inputNames[0]];
        const Signal& inputSignal2 = outputs[inputNames[1]];

        // Вычисляем выходное значение сумматора
        outputs[name] = (*summator)(inputSignal1, inputSignal2);
    }

    return outputs;
}


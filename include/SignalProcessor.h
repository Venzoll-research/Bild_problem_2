#ifndef SIGNALPROCESSOR_H
#define SIGNALPROCESSOR_H

#include <map>
#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include "FilterBase.h"
#include "FIR.h"
#include "IIR.h"
#include "Summator.h"

// Класс для обработки сигнала
class SignalProcessor {
public:
    // Конструктор
    SignalProcessor();
    // Деструктор
    ~SignalProcessor();

    // Копирующий конструктор
    SignalProcessor(const SignalProcessor& other);
    // Оператор присваивания
    SignalProcessor& operator=(const SignalProcessor& other);

    // Перемещающий конструктор
    SignalProcessor(SignalProcessor&& other) noexcept;
    // Перемещающий оператор присваивания
    SignalProcessor& operator=(SignalProcessor&& other) noexcept;

    // Метод для добавления фильтра
    void addFilter(const std::string& name, std::unique_ptr<FilterBase> filter);
    // Метод для добавления сумматора
    void addSummator(const std::string& name, std::unique_ptr<Summator> summator);
    // Метод для установки входного сигнала
    void setInputSignal(const std::string& inputName, const Signal& inputSignal);
    // Метод для добавления связи между блоками
    void addConnection(const std::string& outputName, const std::string& inputName);
    // Метод для расчета выходов всех фильтров для данного входного сигнала
    std::map<std::string, Signal> processSignal();

private:
    std::map<std::string, std::unique_ptr<FilterBase>> filters; // Ассоциативный массив фильтров
    std::map<std::string, std::unique_ptr<Summator>> summators; // Ассоциативный массив сумматоров
    std::map<std::string, Signal> inputSignals; // Входные сигналы
    std::map<std::string, std::vector<std::string>> connections; // Контейнер связей между блоками
};

#endif // SIGNALPROCESSOR_H


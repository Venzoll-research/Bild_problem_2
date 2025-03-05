
import signal_processor as sp

def main():
    # Создание фильтров
    fir_coeffs = [0.2, 0.2, 0.2, 0.2, 0.2]
    iir_b_coeffs = [0.2, 0.2, 0.2, 0.2, 0.2]
    iir_a_coeffs = [1.0, -0.5]

    fir1 = sp.FIR("FIR1", fir_coeffs)
    iir2 = sp.IIR("IIR2", iir_b_coeffs, iir_a_coeffs)

    # Создание сумматора
    summator = sp.Summator("SUM1", 1.0, 1.0)

    # Создание процессора
    processor = sp.SignalProcessor()

    # Добавление компонентов
    processor.addFilter("FIR1", fir1)
    processor.addFilter("IIR2", iir2)
    processor.addSummator("SUM1", summator)

    # Входные сигналы
    input_signal1 = sp.Signal([1.0, 2.0, 3.0, 4.0, 5.0])
    input_signal2 = sp.Signal([5.0, 4.0, 3.0, 2.0, 1.0])

    processor.setInputStream("FIR1", input_signal1)
    processor.setInputStream("IIR2", input_signal2)

    # Настройка связей
    processor.addConnection("SUM1", "FIR1")
    processor.addConnection("SUM1", "IIR2")

    # Обработка сигналов
    outputs = processor.processSignal()

    # Вывод результатов
    for name, signal in outputs.items():
        print(f"{name}: {signal.getValues()}")

if __name__ == "__main__":
    main()
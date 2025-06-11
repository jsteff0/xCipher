# 🔐 xCipher

**xCipher** — это лёгкий и эффективный инструмент для симметричного шифрования и дешифрования текста.  
Он создан для изучения криптографии, демонстрации шифрования и безопасной работы с сообщениями.

## 🛠 Возможности

- Шифрование и дешифрование строк
- Поддержка пользовательских ключей (например, 128 бит)
- Простая CLI-интерфейсная реализация
- Гибкость для расширения

## 🚀 Быстрый старт

### 📥 Клонируй проект

```bash
git clone https://github.com/jsteff0/xCipher.git
cd xCipher
```
### ▶️ Запуск
Исполняемые файлы уже собраны и находятся в папке cli/:
```
./cli/encrypt
```
```
./cli/decrypt
```
## 📁 Структура проекта
```
xCipher/
├── cli/                 # Готовые исполняемые файлы (encrypt, decrypt)
├── .gitignore           # Файл с правилами игнорирования для Git
├── decrypt.cpp          # Исходный код для расшифровки
├── encrypt.cpp          # Исходный код для шифровки
├── xCipher_utils.cpp    # Вспомогательные функции для проекта
├── xCipher_utils.h      # Заголовочный файл с объявлениями вспомогательных функций
└── README.md            # Документация проекта
```

## 🧪 Примеры
### Шифровка:
```
$ ./cli/encrypt                                                           
Enter message:
Hello, world!
Enter key (hex, 32 chars):
00112233445566778899aabbccddeeff

Your ciphertext is 7def9813a1deb620ad8caa2eefb68a86
```
### Расшифровка:
```
$ ./cli/decrypt                                                           
Enter message:
7def9813a1deb620ad8caa2eefb68a86
Enter key (hex, 32 chars):
00112233445566778899aabbccddeeff

Your ciphertext is Hello, world!
```

👤 Автор
Dmitrii Stiufliaev

📧 dimastuflyaev2@gmail.com

🔗 github.com/jsteff0

🔗 t.me/jsteff0

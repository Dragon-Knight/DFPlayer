# DFPlayer
Arduino library for DFPlayer module








### Методы класса

| Метод | Описание | Параметры |
| --- | --- | --- |
| `DFPlayer(uint8_t TXPin, uint8_t busyPin)` | Конструктор класса | `TXPin` - Пин передачи данных (на модуле пин RX)<br>`busyPin` - Пин состояния модуля |
| `DFPlayer(SoftwareSerial &serial, uint8_t busyPin)` | Конструктор класса | `serial` - Ссылка на объект SoftwareSerial<br>`busyPin` - Пин состояния модуля |
| `void Begin()` | Инициализация класса и плеера | - |
| `bool IsBusy()` | Проверка плеера на занятость | - |
| `bool IsReadyReceive()` | Проверка возможности отправки новой команды | - |
| `void PlayNext()` | Следующий трек в текущей папки | - |
| `void PlayPrevious()` | Предыдущий трек в текущей папки | - |
| `void PlayROOT(uint16_t track)` | Воспроизвести файл из корневой папки flash карты | `track` - Номер файла в корневой папке |
| `void VolumeUp()` | Увеличить громкость | - |
| `void VolumeDown()` | Уменьшить громкость | - |
| `void SetVolume(uint8_t volume)` | Установить громкость | `volume` - Уровень громкости, 0..31 |
| `void SetEQ(DFPlayerEqualizer eq)` | Установить эквалайзер | `eq` - Режим эквалайзера |
| `void PlaybackMode(uint8_t mode)` | Режим воспроизведения (?) | ? |
| `void Sleep()` | Перевести модуль в режим энергосбережения | - |
| `void Reset()` | Сбросить модуль | - |
| `void Play()` | Воспроизвести после паузы | - |
| `void Pause()` | Поставить на паузу | - |
| `void PlayNUM(uint8_t folder, uint8_t track)` | Воспроизвести файл из номерных папок | `folder` - Номер папки<br>`track` - Номер трека |
| `void PlayMP3(uint16_t track)` | Воспроизвести файл из папки 'MP3' | `track` - Номер трека |
| `void PlayADVERT(uint16_t track)` | Воспроизвести рекламный файл из папки 'ADVERT' | `track` - Номер трека |
| `void StopAdvert()` | Остановить воспроизведение рекламного файла | - |
| `void Stop()` | Остановить воспроизведение | - |
| `void PlayBySourse(uint16_t param1, uint8_t param2, DFPlayerSourse source)` | Воспроизвести файл из указанного источника | `param1`,`param2` - параметры выбранного источника<br>`source` - Тип источника |
| `void Processing(uint32_t currentMicroTime)` | Обработка очереди воспроизведения | currentMicroTime - Текущее время. Параметр не обязателен.
| `bool QueueAddTop(uint16_t param1, uint8_t param2, DFPlayerSourse source)` | Добавить файл в начало очереди воспроизведения | `param1`,`param2` - параметры выбранного источника<br>`source` - Тип источника |
| `bool QueueAddEnd(uint16_t param1, uint8_t param2, DFPlayerSourse source)` | Добавить файл в конец очереди воспроизведения | `param1`,`param2` - параметры выбранного источника<br>`source` - Тип источника |
| `void QueueClear()` | Очистить очередь воспроизведения | - |

#include <Clapi.h>

// задаём коды команд, которые будет понимать ардуинка
// define the command codes the arduino will understand
#define CMD_SUM       1 /* команда "сложить" */
#define CMD_MULTIPLY  2 /* команда "умножить" */
#define CMD_SAY_HELLO 3 
#define CMD_BLINK     4
#define CMD_TEST      5

// можно объявить экземпляр как Clapi api; но тогда не будет работать оператор ->
// поэтому пишем через new Clapi();
Clapi *api = new Clapi();

// обработчик команд
void listener(int code, int argsCount, float args[]) {
  switch(code) {
    case CMD_SUM:
    // если пришла команда "сложить", то отправим назад сумму двух аргументов
    api ->query("sum", args[0]+args[1])->send();
    break;
    
    case CMD_MULTIPLY:
    // если пришла команда "умнижить", то отправим назад сумму двух аргументов
    api ->query("mult", args[0]*args[1])->send();
    break;
    
    case CMD_SAY_HELLO:
    // отправим назад приветствие
    api ->query("message", "HELLO WORLD")->send();
    break;
    
    case CMD_BLINK:
    // помигаем светодиодом
    for (int i = 0; i < 3; i++) {
      digitalWrite(13, HIGH); delay(300);
      digitalWrite(13, LOW); delay(300);
    }
    break;

    case CMD_TEST:
    // все эти типы данных можно отправить Raspberry в ответ
    api ->query("some_int", 12345)
        ->query("some_float", 3.51)
        ->query("some_text", "hello world")
        ->query("some_boolean", true)
        ->query("another_bool", false)
        ->query("tlbntl_char", 'k')
        ->send();
    break;
  }
}

void setup() {
  api->init(); // там внутри происходит Serial.begin(115200);
  api->setMessageListener(listener);
  api->query("device_id","test")->send();
}

void loop() {
  // просто всё время чекаем, не пришло ли сообщение от Raspberry
  api->processInput();
}


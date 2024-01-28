/* arith.c */
void subtract(ADDR s);
/* control.c */
void stop(ADDR s);
void unused(ADDR s);
void test(ADDR s);
void jump(ADDR s);
void rjump(ADDR s);
/* cursor.c */
void show_cursor(void);
void erase_cursor(void);
void place_cursor(ADDR line,uint16_t bit);
void move_cursor(int16_t d_line,int16_t d_bit);
void toggle_current_bit(void);
void display_current_bit(void);
/* display.c */
void display_bit(int16_t tube,ADDR line,uint16_t bit);
void display_line(int16_t tube,ADDR line);
/* edit.c */
int16_t edit(void);
void toggle_bit(ADDR line,uint16_t bit);
/* exec_ins.c */
void exec_instruction(void);
/* execute.c */
void execute(void);
/* fetch.c */
void fetch_instruction(void);
/* graphics.c */
void set_up_graphics(void);
void clear_graphics(void);
void set_up_line(LINE value);
void show_line(uint16_t x,uint16_t y);
/* init.c */
void initialize(void);
void clean_up(void);
void process_options(int argc,char *argv[]);
/* madm.c */
/* main.c */
int main(int argc,char *argv[]);
/* memory.c */
void load_negative(ADDR s);
void store_accumulator(ADDR s);

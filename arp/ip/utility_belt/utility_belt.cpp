/* utility_belt.cpp */

/* Função que troca as posições dos bytes de uma palavra */
void exchange_endian(unsigned char *v) {
    unsigned char tmp;
    for(int i = 0; i < 2; i++) {
        tmp = v[i];
        v[i] = v[3 - i];
        v[3 - i] = tmp;
    }
}

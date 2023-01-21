
 void iic(String x){
  for(int i=2;i<I2C_NUM;i++){
    Wire.beginTransmission(i);
    char c[x.length()+1];
    x.toCharArray(c,x.length()+1);
    Wire.write(0);
    DPRINTLN("Sent I2c");
    Wire.endTransmission();
  }
}

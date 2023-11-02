// Kalman Filter
#pragma once
float Xt, Xt_update, Xt_prev;
float Pt, Pt_update, Pt_prev = 1;
float Kt, R = 100, Q = 1;
float kalman_data;

void kalman_filter(float _data_){
   Xt_update = Xt_prev;
   Pt_update = Pt_prev + Q;
   Kt = Pt_update/(Pt_update + R);
   Xt = Xt_update + (Kt*(_data_ - Xt_update));
   Pt = (1 - Kt)*Pt_update;
   Xt_prev = Xt;
   Pt_prev = Pt;
   kalman_data = Xt;
}

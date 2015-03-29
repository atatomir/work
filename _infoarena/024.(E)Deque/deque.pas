type element=record
       v,pos:longint;
     end;
var n,i,j,t,k,x:longint;
    deque:array[1..5000000]of element;
    bufin:array[1..65000]of byte;
    sum:int64;

begin
  assign(input,'deque.in'); reset(input);
  assign(output,'deque.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,k);

  i := 1; j := 0;  sum := 0;
  for t := 1 to n do
  begin
    readln(x);
    if j >= i then
      while deque[j].v > x do
      begin
        dec(j);
        if j < i then break;
      end;
    inc(j); deque[j].v := x; deque[j].pos := t;
    if deque[i].pos <= t - k then inc(i);
    if t >= k then sum := sum + deque[i].v;
  end;

  writeln(sum);

  close(input);
  close(output);
end.

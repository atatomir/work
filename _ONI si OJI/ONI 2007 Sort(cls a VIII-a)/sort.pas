var n,i:longint;
    r:array[1..3,1..3]of longint;
    n1,n2,n3,x,cont,min:longint;
    bufin:array[1..65000]of byte;

begin
  assign(input,'sort.in'); reset(input);
  assign(output,'sort.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n);
  n1 := 0; n2 := 0; n3 := 0;
  for i := 1 to n do
  begin
    read(n);
    case n of
      1:inc(n1);
      2:inc(n2);
      3:inc(n3);
    end;
  end;

  for i := 1 to 3 do
  begin
    r[i,1] := 0; r[i,2] := 0; r[i,3] := 0;
  end;

  reset(input);
  readln(n);
  for i := 1 to n1 do
  begin
    read(x);
    inc(r[1,x]);
  end;
  for i := 1 to n2 do
  begin
    read(x);
    inc(r[2,x]);
  end;
  for i := 1 to n3 do
  begin
    read(x);
    inc(r[3,x]);
  end;

  cont := 0;

  min := r[1,2]; if r[2,1] < min then min := r[2,1];
  r[1,2] := r[1,2] - min; r[2,1] := r[2,1] - min; cont := cont + min;
  //writeln(cont);

  min := r[1,3]; if r[3,1] < min then min := r[3,1];
  r[1,3] := r[1,3] - min; r[3,1] := r[3,1] - min; cont := cont + min;
  //writeln(cont);

  min := r[2,3]; if r[3,2] < min then min := r[3,2];
  r[2,3] := r[2,3] - min; r[3,2] := r[3,2] - min; cont := cont + min;
  //writeln(cont);

  cont := cont + 2*r[1,2] + 2*r[1,3];

  writeln(cont);

  close(input);
  close(output);
end.

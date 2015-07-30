var n,i,j,minl,ming,rezmin:longint;
    a:array[0..105,1..6]of byte;
    f1,f2,f3,f4,f5,f6:byte;

procedure send_it(cub,f1,f2,f3,f4,f5,f6:byte);inline;
var cont:byte;
begin
  cont := 0;
  if f1 <> a[cub,1] then inc(cont);
  if f2 <> a[cub,2] then inc(cont);
  if f3 <> a[cub,3] then inc(cont);
  if f4 <> a[cub,4] then inc(cont);
  if f5 <> a[cub,5] then inc(cont);
  if f6 <> a[cub,6] then inc(cont);
  if cont < minl then minl := cont;
end;

procedure try_it(cub,f1,f2,f3,f4,f5,f6:byte); inline;
begin
  minl := 16;

  send_it(cub,f1,f2,f3,f4,f5,f6);
  send_it(cub,f1,f5,f3,f6,f4,f2);
  send_it(cub,f1,f4,f3,f2,f6,f5);
  send_it(cub,f1,f6,f3,f5,f2,f4);

  if minl < ming then ming := minl;
end;

procedure verifica();inline;
var cub,min:longint;
begin
  min := 0;

  for cub := 1 to n do
  begin
    ming := 16;

    try_it(cub,f1,f2,f3,f4,f5,f6);
    try_it(cub,f6,f2,f5,f4,f1,f3);
    try_it(cub,f3,f2,f1,f4,f6,f5);
    try_it(cub,f5,f2,f6,f4,f3,f1);
    try_it(cub,f2,f3,f4,f1,f5,f6);
    try_it(cub,f4,f1,f2,f3,f5,f6);

    min := min + ming;
  end;

  if min < rezmin then rezmin := min;
end;

begin
 { assign(input,'boxes.in'); reset(input);
  assign(output,'boxes.out'); rewrite(output);
  }
  readln(n);
  for i:= 1 to n do
  begin
    for j := 1 to 6 do read(a[i,j]);
    readln();
  end;

  rezmin := 5000000;

  for f1 := 0 to 6 do
    for f2 := 0 to 4 do
      for f3 := 0 to 4 do
        for f4 := 0 to 4 do
          for f5 := 0 to 4 do
            for f6 := 0 to 4 do
              verifica();


  writeln(rezmin);
  {
  close(input);
  close(output);}
end.

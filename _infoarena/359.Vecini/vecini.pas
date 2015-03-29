var a:array[1..100001]of byte;
    bufout:array[1..65000]of byte;
    lung,n,i:longint;

procedure genereaza(ant:longint);
var putere:longint;
begin
  putere := 1;
  while putere*2 <= ant do
  begin
    putere := putere*2;
  end;

  if putere <> ant then
    genereaza(ant-putere)
  else
  begin
    lung := putere;
    for i := 1 to lung do a[i] := 1;
    exit;
  end;

  for i := lung + 1 to ant-lung do
    a[i] := 0;
  for i := ant-lung+1 to ant do
    a[i] := a[i-ant+lung];
  lung := ant;
end;


begin
  assign(input,'vecini.in'); reset(input);
  assign(output,'vecini.out'); rewrite(output);
  settextbuf(output,bufout);

  read(n); lung := 0;

  genereaza(n);

  for i := 1 to lung do write(a[i],' ');

  close(input);
  close(output);
end.
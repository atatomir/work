const alfabet = 'abcdefghijklmnopqrstuvwxyz';

var bufin:array[1..65000]of byte;
    i,n:longint;
    x:char;
    a:array[97..122] of longint;
    iesit:boolean;

begin
  assign(input,'dinozaur.in'); reset(input);
  assign(output,'dinozaur.out'); rewrite(output);
  settextbuf(input,bufin);

  for i := 97 to 122 do a[i] := 0;
  iesit := false;

  while not eof(input) do
  begin
    read(x);
    if pos(x,alfabet)> 0 then
    begin
      inc(a[ord(x)]);
      if a[ord(x)] > 1 then
      begin
        iesit := true;
        break;
      end;
    end;
  end;

  if iesit= true then write('1') else write('0');


  close(input);
  close(output);
end.
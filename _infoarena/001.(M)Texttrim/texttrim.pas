var a:array[30..150]of longint;
    w,i,we,j:longint;
    s:ansistring;
    buffin,buffout:array[1..65000]of byte;
    suma:int64;

begin
  assign(input,'texttrim.in'); reset(input);
  assign(output,'texttrim.out'); rewrite(output);
  settextbuf(input,buffin);
  settextbuf(output,buffout);

  read(a[32]);         //citire
  for i := $61 to $7A do
    read(a[i]);
  readln();
  readln(s);
  read(w);        //ecitire


  we := w -3; suma := 0; i:=1;

  while  (suma + a[ord(s[i])] <= we) and (i<=length(s)) do
  begin
    suma := suma + a[ord(s[i])];
    write(s[i]);
    inc(i);
  end;

  i := i -1;

  if length(s) - i > 3 then
    write('...')
  else
  begin
    for j := i+1 to length(s) do
      suma := suma + a[ord(s[j])];
    if suma <= w then
    begin
      for j := i+1 to length(s) do
        write(s[j]);
    end
    else
      write('...');
  end;



  close(input);
  close(output);

end.

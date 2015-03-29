var s:ansistring;
    bufin:array[1..65000]of byte;
    i,cont:longint;
    scrie:boolean;

begin
  assign(input,'egalitati.in'); reset(input);
  assign(output,'egalitati.out'); rewrite(output);
  settextbuf(input,bufin);
  read(s);
  i := 1; cont :=0;
  while s[i] <> '.' do
  begin
    scrie := true;
    case s[i] of
    '(': inc(cont);
    ')': begin
           cont := cont -1;
           if cont < 0 then
           begin
             inc(i);
             while (s[i] <> ';') and (s[i] <> '.') do
             begin
               inc(i);
             end;
             writeln('0');
             cont := 0;
             scrie := false;
           end;
         end;
    '=': begin
           if cont <>0 then
           begin
             inc(i);
             while (s[i] <>';') and (s[i] <> '.') do
             begin
               inc(i);
             end;
             writeln('0');
             cont :=0;
             scrie:=false;
           end;
         end;
    ';': begin
           if cont = 0 then writeln('1') else writeln('0');
           cont :=0;
         end;
    end;

    if s[i] <> '.' then inc(i);
  end;

  if scrie = true then
    if cont = 0 then writeln('1') else writeln('0');

  close(input); close(output);
end.

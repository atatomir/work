var cont,i,j,x:longint;
    zero:boolean;

begin
  assign(input,'cpal.in'); reset(input);
  assign(output,'cpal.out'); rewrite(output);

  for i := 1 to 10 do
  begin
    cont := 0; zero := true;

    for j := 1 to 9 do
    begin
      read(x);
      if x > 0 then zero := false;
      cont := cont + (x mod 2);
    end;

    if (cont < 2) and (zero=false) then writeln('1') else writeln('0');
    readln();
  end;




  close(input);
  close(output);
end.
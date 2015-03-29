var bufin:array[1..65000]of byte;
    n,m:longint;
    per:array[1..100000]of boolean;
    i,x,y,t:longint;
    max:int64;
    iesi:boolean;

begin
  assign(input,'dmin2.in'); reset(input);
  assign(output,'dmin2.out'); rewrite(output);
  settextbuf(input,bufin);

  readln(n,m);  iesi := false;
  if n <= 3 then
    write('0')
  else
  begin

    for i := 2 to n-1 do
      per[i] := false;

    for i := 1 to  m do
    begin
      readln(x,y);

      if x > y then
      begin
        t := x;
        x := y;
        y := t;
      end;
      if (x=1) and (y=n) then
      begin
        iesi := true;
        break;
      end
      else
      begin
        if x=1 then
        begin
          if per[y]= false then
            per[y] := true
          else
          begin
            iesi := true;
            break;
          end;
        end
        else
        begin
          if y = n then
          begin
            if per[x] = false then
              per[x] := true
            else
            begin
              iesi := true;
              break;
            end;
          end;
        end;
      end;
    end;
    if iesi = true then
      write('0')
    else
    begin
      max := (n-1)*(n-2) div 2 ;
      max := max - m ;
      if max<0 then max := 0;
      write(max);
    end;
  end;



  close(input);
  close(output);
end.

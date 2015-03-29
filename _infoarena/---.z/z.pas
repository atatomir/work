var n,k,i,j,i2,j2,t,x,y,ii,jj,h,h2:longint;

function puterea(n:longint):longint;
var i:longint;
begin
  puterea := 1;
  for i := 1 to n do puterea := puterea*2;
end;
begin
  assign(input,'z.in'); reset(input);
  assign(output,'z.out'); rewrite(output);

  readln(n,k);
  h := puterea(n);

  for t := 1 to k do
  begin
    readln(x,y);
    i := 1; j := 1; i2 := h; j2 := h;
    ii := 1; jj := h*h;
    while (x <> i)or(y <> j) do
    begin
      if x <= i-1+ (i2-i+1) div 2 then
      begin
        if y <= j-1 +(j2-j+1) div 2 then
        begin                 //sus stanga
          i2 := i-1 + (i2-i+1) div 2;
          j2 := j-1 + (j2-j+1) div 2;
          jj := ii-1 + (jj-ii+1) div 4;
        end
        else
        begin                  //sus dreapta
          j := j + (j2-j+1)div 2 ;
          i2 := i-1 + (i2-i+1) div 2;   h2 := ii;
          ii := ii + (jj-ii+1) div 4;
          jj := h2 + (jj-h2+1) div 2;
        end;
      end
      else
      begin
        if y <= j-1 + (j2-j+1) div 2 then
        begin                 //jos stanga
          i := i + (i2-i+1)div 2;
          j2 := j-1 + (j2-j+1)div 2;      h2 := ii;
          ii := ii + (jj-ii+1)div 2;
          jj := h2-1 + ((jj-h2+1)div 4)*3;
        end
        else
        begin                   //jos dreapta
          i := i + (i2-i+1) div 2;
          j := j + (j2-j+1) div 2;
          ii := ii + ((jj-ii+1) div 4)*3;
        end;
      end;

    end;

    writeln(ii);
  end;



  close(input);
  close(output);
end.
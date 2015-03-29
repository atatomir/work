var wf,hf,wp,hp,d1,d2,scale:real;


begin
  assign(input,'scalecrop.in'); reset(input);
  assign(output,'scalecrop.out'); rewrite(output);

  readln(wf,hf,wp,hp);

  d1 := wf - wp;
  if d1 < 0 then d1 := d1 * (-1);
  d2 := hf - hp;
  if d2 < 0 then d2 := d2 * (-1);

  if (wp - wf < 0) and (hp - hf > 0) then d1 := d2 -1;
  if (wp - wf > 0) and (hp - hf < 0) then d2 := d1 -1;
  if (wp - wf < 0) and (hp - hf < 0) then
    if d1 < d2 then d1 := d2+1 else d2 := d1+1;

  if d1 < d2 then
  begin
    scale := wf / wp;
    write(wf,' ',scale*hp);
  end
  else
  begin
    scale := hf / hp;
    write(wp*scale,' ',hf);
  end;




  close(input);
  close(output);
end.

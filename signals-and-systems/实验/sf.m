function y = sf(t,w)
y=(abs(t)<=1).*(1-abs(t)).*exp(-j*w*t);
end
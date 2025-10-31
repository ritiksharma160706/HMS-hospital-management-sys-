function toggleSidebar(){
  document.querySelector('.sidebar').classList.toggle('open');
}
function showToast(msg){
  const t=document.createElement('div'); t.textContent=msg;
  t.style='position:fixed;right:20px;bottom:20px;padding:12px 16px;background:#062c33;color:#bff1ff;border-radius:10px;box-shadow:0 6px 20px rgba(2,6,23,0.6);z-index:9999';
  document.body.appendChild(t); setTimeout(()=>t.remove(),2200);
}

var techId

var modal = document.getElementById('deleteModal')
modal.addEventListener('show.bs.modal', function(event) {
    var button = event.relatedTarget
    techId = button.getAttribute('data-bs-techId')
    console.log(techId)
    var modalText = modal.querySelector('.modal-text')

    modalText.textContent = 'Êtes vous sur de vouloir supprimer ce technicien du CAI ? Dans le cas échéant vous devrez lui donné 100%'
})

function toDelete(){
    window.location.href="/admin/delete?techId=" + techId
}
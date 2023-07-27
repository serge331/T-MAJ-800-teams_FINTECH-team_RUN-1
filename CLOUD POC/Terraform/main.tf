resource "ovh_cloud_project_user" "user1" {
  service_name = var.cluster_project-id
  description  = "user_terraform"
  role_name    = "administrator"
}

# Association du projet cloud au vRack
resource "ovh_vrack_cloudproject" "vcp" {
  service_name = "pn-1087329"
  project_id   = var.cluster_project-id
} 

resource "ovh_cloud_project_network_private" "network" {
  service_name = var.cluster_project-id
  name         = "Private_Network"
  regions      = [var.cluster_region]
  vlan_id      = 0
  depends_on   = [ovh_vrack_cloudproject.vcp]
}

resource "ovh_cloud_project_network_private_subnet" "network_sub" {
  service_name = var.cluster_project-id
  network_id   = ovh_cloud_project_network_private.network.id
  region       = var.cluster_region
  start        = "10.0.0.2"
  end          = "10.0.255.254"
  network      = "10.0.0.0/16"
  #start        = "192.168.0.2"
  #end          = "192.168.0.254"
  #network      = "192.168.0.0/24"
  dhcp         = false
  no_gateway   = true
}

resource "ovh_cloud_project_kube" "cluster" {
  service_name       = var.cluster_project-id
  name               = var.cluster_name
  region             = var.cluster_region
  version            = var.cluster_version
  private_network_id = tolist(ovh_cloud_project_network_private.network.regions_attributes)[0].openstackid
}

resource "ovh_cloud_project_kube_iprestrictions" "iprestric" {
  service_name       = var.cluster_project-id
  kube_id            = ovh_cloud_project_kube.cluster.id
  ips                = var.cluster_ip_restriction
}

resource "ovh_cloud_project_kube_nodepool" "node_pool" {
  service_name   = var.cluster_project-id
  kube_id        = ovh_cloud_project_kube.cluster.id
  name           = var.cluster_poolname != "" ? var.cluster_poolname : "pool-${var.cluster_name}"
  flavor_name    = var.cluster_type_vm
  monthly_billed = var.cluster_monthly_billed
  anti_affinity  = var.cluster_anti_affinity
  autoscale      = var.cluster_autoscale
  desired_nodes  = var.cluster_desired_nodes
  max_nodes      = var.cluster_max_nodes
  min_nodes      = var.cluster_min_nodes
}
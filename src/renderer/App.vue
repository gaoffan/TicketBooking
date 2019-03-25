<template>
  <div id="app">
  <el-container style="border: 0px solid;">
  <el-aside width="200px">
  <el-menu default-active="1-4-1" class="el-menu-vertical-demo" @open="handleOpen" @close="handleClose" :collapse="isCollapse"
  background-color="#545c64"
  text-color="#fff"
  active-text-color="#ffd04b">
  <el-menu-item index="1">
    <i class="el-icon-menu"></i>
    <span slot="title"><router-link to="/">在线订票</router-link></span>
    </el-menu-item>
    <el-menu-item index="2">
      <i class="el-icon-document"></i>
      <span slot="title"><router-link to="/showresult">我的订单</router-link></span>
    </el-menu-item>
    <el-menu-item index="3">
      <i class="el-icon-setting"></i>
      <span slot="title"><router-link to="/addTrainNumber">管理面板</router-link></span>
    </el-menu-item>
  </el-menu>
  </el-aside>
  <el-main><router-view></router-view></el-main>
  </el-container>

</div>
</template>

<script>
  export default {
    name: 'ticket-booking',
    data () {
      return {
        activeIndex: '1',
        activeIndex2: '1'
      }
    }
  }
</script>

<style>
  /* CSS */
  body {
    font-family: "Helvetica Neue",Helvetica,"PingFang SC","Hiragino Sans GB","Microsoft YaHei","微软雅黑",Arial,sans-serif;
  }
</style>
